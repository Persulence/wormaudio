#pragma once

#include <functional>
#include "../signal/Signal.hpp"

#include "juce_core/system/juce_PlatformDefs.h"

namespace player
{
    enum TransportState
    {
        STOPPED,
        STARTING,
        PLAYING,
        STOPPING
    };

    using TransportCallback1 = std::function<void(TransportState)>;
    using TransportCallback = signal_event::Callback<TransportState>;

    class TransportControl
    {
        TransportState state{STOPPED};

        JUCE_DECLARE_NON_COPYABLE(TransportControl)
    public:
        TransportCallback::Signal signal;

        TransportControl() = default;

        void setState(TransportState state_);
        [[nodiscard]] bool stopped() const;
    };

}

