#pragma once
#include "ParameterConfigWidget.hpp"
#include "juce_gui_basics/juce_gui_basics.h"

import sm;

import parameter;

namespace ui
{
    class ParameterWidget : public juce::Component, public ParameterConfig::OnChange::Listener
    {
        std::unique_ptr<Component> child;
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
