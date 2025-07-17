// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once
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
