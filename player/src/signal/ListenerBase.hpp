#pragma once
#include "SharedSignal.hpp"

namespace signal_event
{
    template <typename... Args>
    class ListenerBase
    {
        friend class SharedSignal<Args...>;
        using Callback = std::function<void(Args...)>;

    public:
        using S = SharedSignal<Args...>;

        virtual ~ListenerBase() = default;

    protected:
        virtual void targetDestroyed(S* target) = 0;

        Callback callback = [](Args...){};
    };
}
