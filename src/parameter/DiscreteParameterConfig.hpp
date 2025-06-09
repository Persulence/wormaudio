#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "signal/Signal.hpp"
#include "ParameterConfigWidget.hpp"

import parameter;

namespace ui
{
    class DiscreteParameterConfig : public ParameterConfig
    {
        juce::Label minValue;
        juce::Label maxValue;
        parameter::DiscreteParameterDef &def;

    public:
        explicit DiscreteParameterConfig(parameter::DiscreteParameterDef& def_):
            def(def_)
        {
            addAndMakeVisible(minValue);
            minValue.setEditable(true);
            minValue.setText(juce::String{def_.min}, juce::dontSendNotification);
            minValue.onTextChange = [this]()
            {
                def.min = std::roundf(parameter::parseValue(minValue.getText().toStdString()));
                onChange.emit();
            };

            addAndMakeVisible(maxValue);
            maxValue.setEditable(true);
            maxValue.setText(juce::String{def_.max}, juce::dontSendNotification);
            maxValue.onTextChange = [this]()
            {
                def.max = std::roundf(parameter::parseValue(maxValue.getText().toStdString()));
                onChange.emit();
            };
        }

        ~DiscreteParameterConfig() override = default;

        void resized() override
        {
            auto rect = getLocalBounds();
            minValue.setBounds(rect.removeFromTop(30));
            maxValue.setBounds(rect.removeFromTop(30));
        }
    };
}
