// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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

