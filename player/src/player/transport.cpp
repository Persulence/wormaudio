// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
