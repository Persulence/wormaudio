module;

#include <functional>
#include "../signal/Signal.hpp"
#include "juce_core/system/juce_PlatformDefs.h"

export module transport;

namespace player
{
    export enum TransportState
    {
        STOPPED,
        STARTING,
        PLAYING,
        STOPPING
    };

    export using TransportCallback1 = std::function<void(TransportState)>;
    export using TransportCallback = signal_event::Callback<TransportState>;

    export class TransportControl
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

