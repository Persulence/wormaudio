#pragma once
#include <algorithm>
#include <vector>

namespace signal_event
{
    template <typename... Args>
    class Signal;

    template <typename... Args>
    class ListenerBase;

    template <typename... Args>
    class Listener;

    template <typename... Args>
    class MultiListener;

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
        using MultiListener = MultiListener<Args...>;
    };

    template <typename... Args>
    class SharedSignal
    {
        using L = ListenerBase<Args...>;

    public:
        SharedSignal(const SharedSignal&) = delete;
        SharedSignal& operator=(const SharedSignal&) = delete;
        SharedSignal(SharedSignal&&) = delete;
        SharedSignal& operator=(SharedSignal&&) = delete;

        SharedSignal() = default;

        ~SharedSignal()
        {
            for (auto& listener : listeners)
            {
                listener->targetDestroyed(this);
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
}
