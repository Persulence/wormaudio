#pragma once

#include "signal/UniqueSignal.hpp"

namespace editor
{
    using EventChanged = signal_event::Callback<>;
    using Lifecycle = signal_event::Callback<int>;
    using ParametersChanged = signal_event::Callback<>;
    using ProjectRefreshed = signal_event::Callback<>;
}
