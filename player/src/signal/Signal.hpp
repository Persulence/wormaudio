#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

namespace signal_event
{
    template <typename... Args>
    class Signal;

    template <typename... Args>
    class Listener;

    /**
     * using Thing = Callback<int, int, int>;
     * Thing::Signal s;
     * Thing::Listener l;
     * l.listen(s, callback);
     * s.emit(1, 2, 3);
     * @tparam Args Parameters of the callback function
     */
    template <typename... Args> struct Callback
    {
        using Signal = Signal<Args...>;
        using Listener = Listener<Args...>;
    };

    /**
     * Provides an automatically deleting connection to a @link Signal.
     * The listener will keep track of the target signal and will unregister itself on destruction.
     * @tparam Args Parameters of the callback function
     */
    template <typename... Args>
    class Listener
    {
        using Callback = std::function<void(Args...)>;

    public:
        // Copy constructor
        Listener() = default;

        Listener(const Listener& other)
        {
            if (other.target)
            {
                other.target->reg(this);
                target = other.target;
            }

            callback = other.callback;
        }

        ~Listener()
        {
            unListen();
        }

        /**
         *
         * Use Signal::register if the listener class inherits from multiple Listener types
         */
        void listen(Signal<Args...>& signal, Callback callback_)
        {
            unListen();
            signal.reg(this);
            target = &signal;
            callback = callback_;
        }

        void unListen()
        {
            if (target)
            {
                target->unReg(this);
                target = nullptr;
            }
        }

        void targetDestroyed()
        {
            target = nullptr;
        }

    private:
        friend class Signal<Args...>;

        Signal<Args...>* target{nullptr};
        Callback callback;
    };

    /**
     *
     * @tparam Args Parameters of the callback function
     */
    template <typename... Args>
    class Signal
    {
        using L = Listener<Args...>;

        class SharedSignal
        {
        public:
            ~SharedSignal()
            {
                for (auto& listener : listeners)
                {
                    listener->targetDestroyed();
                }
            }

            void reg(L* listener)
            {
                listeners.push_back(listener);
            }

            void unReg(L* listener)
            {
                listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
            }

            void emit(Args... args)
            {
                for (auto& l : listeners)
                {
                    l->callback(std::forward<Args>(args)...);
                }
            }

        private:
            std::vector<L*> listeners;
            // TODO: mutex
        };

    public:
        using Callback = std::function<void(Args...)>;

        void reg(L* listener)
        {
            ptr->reg(listener);
        }

        void setup(L* listener, Callback callback_)
        {
            listener->listen(*this, callback_);
        }

        void unReg(L* listener)
        {
            ptr->unReg(listener);
        }

        void emit(Args... args)
        {
            ptr->emit(args...);
        }

    private:
        std::unique_ptr<SharedSignal> ptr{std::make_unique<SharedSignal>()};
    };
}
