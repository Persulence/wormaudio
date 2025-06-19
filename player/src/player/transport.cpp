#include "transport.hpp"

namespace player
{
    void TransportControl::setState(TransportState state_)
    {
        state = state_;
        signal.emit(state);
    }

    bool TransportControl::stopped() const
    {
        return state == STOPPED;
    }
}
