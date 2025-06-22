#pragma once

#include <algorithm>
#include <functional>
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

        Signal<Args...>* target{nullptr};
        Callback callback;

        friend class Signal<Args...>;

    public:
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
    };

    /**
     *
     * @tparam Args Parameters of the callback function
     */
    template <typename... Args>
    class Signal
    {
        using L = Listener<Args...>;

        std::vector<L*> listeners;
        // TODO: mutex

    public:
        using Callback = std::function<void(Args...)>;

        ~Signal()
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

        void setup(L* listener, Callback callback_)
        {
            listener->listen(*this, callback_);
        }

        void unReg(L* listener)
        {
            listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
            // listeners.erase(std::ranges::remove(listeners, listener), listeners.end());
            // if (auto it = std::ranges::find(listeners, listener); it != listeners.end())
            // {
            //     listeners.erase(it);
            // }
        }

        void emit(Args... args)
        {
            for (auto& l : listeners)
            {
                l->callback(std::forward<Args>(args)...);
            }
        }
    };

    // inline void signalTest()
    // {
    //     // using Thing = std::function<void(int)>;
    //     using Thing = Callback<int, bool>;
    //
    //     // Signal<int> s;
    //     Thing::Signal s;
    //
    //     Thing::Listener l;
    //     l.listen(s, [](int i, bool b) { std::cout << i << "\n"; });
    //
    //     s.emit(123, false);
    // }
}
