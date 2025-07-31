// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include <functional>

#include "UniqueSignal.hpp"

namespace signal_event
{
    template <typename... Args>
    class ListenerBase
    {
        friend class UniqueSignal<Args...>;
        using Callback = std::function<void(Args...)>;

    public:
        using S = UniqueSignal<Args...>;

        virtual ~ListenerBase() = default;
        // virtual void listen(Signal<Args...>& signal, Callback callback_) = 0;

    protected:
        virtual void targetDestroyed(const UniqueSignal<Args...> *target) = 0;

        Callback listenerCallback;
    };


    // template<typename... Args>
    // struct ListenerEraser
    // {
    //     using Callback = std::function<void(Args...)>;
    //
    //     explicit ListenerEraser(auto listener)
    //     {
    //         listen = [listener](auto& signal, auto callback)
    //         {
    //             listener.listen(signal, callback);
    //         };
    //
    //         invoke = [listener](Args... args)
    //         {
    //             listener.callback(args...);
    //         };
    //     }
    //
    //     std::function<void(Signal<Args...>&, Callback)> listen;
    //     std::function<void(Args...)> invoke;
    // };
}
