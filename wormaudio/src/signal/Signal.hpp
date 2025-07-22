// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
    class SignalType
    {
        using L = ListenerBase<Args...>;

    public:
        using Callback = std::function<void(Args...)>;

        SignalType(): ptr(std::make_unique<UniqueSignal<Args...>>()) {}

        void reg(L* listener)
        {
            ptr->reg(listener);
        }

        void setup(MultiListenerType<Args...>* listener)
        {
            listener->listen(*this);
        }

        void setup(ListenerType<Args...>* listener)
        {
            listener->listen(*this);
        }

        void setup(ListenerType<Args...>* listener, Callback callback_)
        {
            listener->listen(*this, callback_);
        }

        void unReg(ListenerType<Args...>* listener)
        {
            ptr->unReg(listener->get());
        }

        void unReg(MultiListenerType<Args...>* listener)
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
