#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "signal/Signal.hpp"

namespace ui
{
    class ParameterConfig : public juce::Component
    {
    public:
        using OnChange = signal_event::Callback<>;
        OnChange::Signal onChange;
    };
}
