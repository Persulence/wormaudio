#pragma once
#include "juce_gui_basics/juce_gui_basics.h"

import parameter;

namespace ui
{
    class ParameterWidget : public juce::Component
    {
        std::unique_ptr<Component> child;
        // parameter::Parameter parameter;
        parameter::ParameterInstance& instance;

    public:
        explicit ParameterWidget(parameter::ParameterInstance& instance);
        void refresh();

        void resized() override;
    };
}
