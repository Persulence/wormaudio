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
#include "../signal/Signal.hpp"
#include "util/Time.hpp"

#include "util/class_util.h"

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

        DISABLE_COPY(TransportControl);
    public:
        TransportCallback::Signal signal;

        TransportControl() = default;

        void setState(TransportState state_);
        TransportState getState() const { return state; }
        [[nodiscard]] bool stopped() const;
    };
}

