#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

#include "ListenerBase.hpp"
#include "SharedSignal.hpp"

namespace signal_event
{
    /**
     * Provides an automatically deleting connection to a @link Signal.
     * The listener will keep track of the target signal and will unregister itself on destruction.
     * @tparam Args Parameters of the callback function
     */
    template <typename... Args>
    class Listener : public ListenerBase<Args...>
    {
        using Callback = std::function<void(Args...)>;

    public:
        Listener() = default;

        Listener(const Listener& other)
        {
            // Register this as a listener
            if (other.target)
            {
                other.target->reg(this);
                target = other.target;
            }

            callback = other.callback;
        }

        // Move
        Listener(Listener&& other) noexcept
        {
            // Unregister the other listener
            other.unListen();
        }

        Listener& operator=(Listener&& other) noexcept
        {
            other.unListen();
            return *this;
        }

        ~Listener() override
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

        void targetDestroyed(typename ListenerBase<Args...>::S* destroyedTarget) override
        {
            this->target = nullptr;
        }

    private:
        friend class Signal<Args...>;

        Signal<Args...>* target{nullptr};
        Callback callback;
    };

    template <typename... Args>
    class MultiListener : public ListenerBase<Args...>
    {
        using Callback = std::function<void(Args...)>;
        using S = SharedSignal<Args...>;

    public:
        MultiListener() = default;

        MultiListener(const MultiListener& other)
        {
            // Register this as a listener
            for (auto& target : other.targets)
            {
                target->reg(this);
            }

            this->callback = other.callback;
        }

        // Move
        MultiListener(MultiListener&& other) noexcept
        {
            // Unregister the other listener
            other.unListen();
        }

        MultiListener& operator=(MultiListener&& other) noexcept
        {
            other.unListen();
            return *this;
        }

        ~MultiListener() override
        {
            unListenAll();
        }

        void listen(Signal<Args...>& signal, Callback callback_)
        {
            unListen();
            signal.reg(this);
            this->callback = callback_;

            targets.emplace_back(signal.get());
        }

        void listen(Signal<Args...>& signal)
        {
            signal.reg(this);

            targets.push_back(signal.get());
        }

        void unListen(Signal<Args...>& target)
        {
            targets.erase(std::remove(targets.begin(), targets.end(), target.get()), targets.end());
            target.unReg(this);
        }

        void unListenAll()
        {
            for (auto& target : targets)
            {
                target->unReg(this);
            }
            targets.clear();
        }

        void setCallback(Callback callback_)
        {
            this->callback = callback_;
        }


    protected:
        void targetDestroyed(typename ListenerBase<Args...>::S *target) override
        {
            targets.erase(std::remove(targets.begin(), targets.end(), target), targets.end());
        }

    private:
        friend class Signal<Args...>;

        std::vector<S*> targets;
    };

    // template <typename... Args>
    // class MultiListener : public ListenerBase<Args...>
    // {
    //     using L = Listener<Args...>;
    //     using Callback = std::function<void(Args...)>;
    //
    // public:
    //     void listen(typename ListenerBase<Args...>::S* target)
    //     {
    //         auto& l =listeners.emplace_back();
    //         l.listen(target, delegateCallback);
    //     }
    //
    //     void setCallback(Callback callback_)
    //     {
    //         callback = callback_;
    //     }
    //
    //     void targetDestroyed(typename ListenerBase<Args...>::S* destroyedTarget) override
    //     {
    //         listeners.clear();
    //     }
    //
    //     // void unListen(typename ListenerBase<Args...>::S* target) override
    //     // {
    //     //
    //     // }
    //
    // private:
    //     std::vector<L> listeners;
    //     Callback callback = [](Args...){};
    //     Callback delegateCallback = [this](Args... args)
    //     {
    //         callback(args...);
    //     };
    // };

    /**
     *
     * @tparam Args Parameters of the callback function
     */
    template <typename... Args>
    class Signal
    {
        using L = ListenerBase<Args...>;

    public:
        using Callback = std::function<void(Args...)>;

        Signal(): ptr(std::make_unique<SharedSignal<Args...>>()) {}

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

        SharedSignal<Args...>* get()
        {
            return ptr.get();
        }

    private:
        std::unique_ptr<SharedSignal<Args...>> ptr;
    };
}
