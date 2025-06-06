#pragma once
#include "juce_gui_basics/juce_gui_basics.h"

import control;

import parameter;

namespace ui
{
    class ParameterWidget : public juce::Component
    {
        std::unique_ptr<Component> child;
        // parameter::ParameterInstance& instance;
        sm::ParameterLookup& lookup;
        parameter::Parameter parameter;
        juce::Label label;

    public:
        explicit ParameterWidget(sm::ParameterLookup& lookup, parameter::Parameter parameter);
        void refresh();

        void resized() override;
        void mouseDown(const juce::MouseEvent &event) override;

    private:
        parameter::ParameterInstance &getParameter() const;
    };
}
