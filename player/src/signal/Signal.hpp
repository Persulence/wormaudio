#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

namespace signal
{
    template <typename... Args>
    class Signal;

    /// The Abomination
    template <typename... P> struct Callback
    {
        template <template <typename...> typename T>
        using apply = T<P...>;
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

        void listen(Signal<Args...>& signal, Callback callback_)
        {
            unListen();
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

    public:
        void reg(L* listener)
        {
            listeners.push_back(listener);
        }

        void unReg(L* listener)
        {
            listeners.erase(std::ranges::find(listeners, listener));
        }

        void emit(Args... args)
        {
            for (auto& l : listeners)
            {
                l->callback(std::forward<Args>(args)...);
            }
        }
    };

    void signalTest()
    {
        // using Thing = std::function<void(int)>;
        using Thing = Callback<int, bool>;

        // Signal<int> s;
        Thing::apply<Signal> s;

        Thing::apply<Listener> l;
        l.listen(s, [](int i, bool b) { std::cout << i << "\n"; });

        s.emit(123, false);
    }
}
