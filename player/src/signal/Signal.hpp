#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

#include "ListenerBase.hpp"
#include "UniqueSignal.hpp"
#include "Listener.hpp"

namespace signal_event
{
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

        Signal(): ptr(std::make_unique<UniqueSignal<Args...>>()) {}

        void reg(L* listener)
        {
            ptr->reg(listener);
        }

        void setup(MultiListener<Args...>* listener)
        {
            listener->listen(*this);
        }

        void setup(Listener<Args...>* listener)
        {
            listener->listen(*this);
        }

        void setup(Listener<Args...>* listener, Callback callback_)
        {
            listener->listen(*this, callback_);
        }

        void unReg(Listener<Args...>* listener)
        {
            ptr->unReg(listener->get());
        }

        void unReg(MultiListener<Args...>* listener)
        {
            ptr->unReg(listener->get());
        }

        void unReg(L* listener)
        {
            ptr->unReg(listener);
        }

        void emit(Args... args)
        {
            ptr->emit(std::forward<Args>(args)...);
        }

        UniqueSignal<Args...>* get()
        {
            return ptr.get();
        }

    private:
        std::unique_ptr<UniqueSignal<Args...>> ptr;
    };
}
