// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "signal/UniqueSignal.hpp"

namespace editor
{
    using EventChanged = signal_event::Callback<>;
    using Lifecycle = signal_event::Callback<int>;
    using ParametersChanged = signal_event::Callback<>;
    using ProjectRefreshed = signal_event::Callback<>;
    using EventChanged = signal_event::Callback<>;
}
