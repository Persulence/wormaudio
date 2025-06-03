#pragma once
#include "juce_gui_basics/juce_gui_basics.h"

import parameter;

namespace ui
{
    class Thing : public juce::Component
    {

    };

    class ParameterWidget : public juce::Component
    {
        std::unique_ptr<Thing> impl;

        explicit ParameterWidget(parameter::Parameter parameter);
    };
}
