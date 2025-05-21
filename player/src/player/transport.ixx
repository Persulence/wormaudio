module;

#include <functional>

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

    export using TransportCallback = std::function<void(TransportState)>;
}

