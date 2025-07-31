// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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

        void emit(Args... args) const
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
