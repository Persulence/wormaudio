#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "signal/Signal.hpp"
#include "ParameterConfigWidget.hpp"

import parameter;


namespace ui
{
    class ContinuousParameterConfig : public ParameterConfig
    {
        // juce::Label minValue;
        // juce::Label maxValue;
        parameter::ContinuousParameterDef &def;

        WrappedValue vMin;
        WrappedValue vMax;

    public:
        JUCE_DECLARE_NON_COPYABLE(ContinuousParameterConfig)
        explicit ContinuousParameterConfig(parameter::ContinuousParameterDef& def_):
            def(def_)
        {
            // addAndMakeVisible(minValue);
            // minValue.setEditable(true);
            // minValue.setText(juce::String{def_.min}, juce::dontSendNotification);
            // minValue.onTextChange = [this]()
            // {
            //     def.min = parameter::parseValue(minValue.getText().toStdString());
            //     onChange.emit();
            // };
            //
            // addAndMakeVisible(maxValue);
            // maxValue.setEditable(true);
            // maxValue.setText(juce::String{def_.max}, juce::dontSendNotification);
            // maxValue.onTextChange = [this]()
            // {
            //     def.max = parameter::parseValue(maxValue.getText().toStdString());
            //     onChange.emit();
            // };

            juce::Value(vMin).setValue(def.min);
            vMin.callback = [this](const juce::Value& val)
            {
                def.min = val.getValue();
                onChange.emit();
            };

            vMax.value.setValue(def.max);
            vMax.callback = [this](const juce::Value& val)
            {
                def.max = val.getValue();
                onChange.emit();
            };

            // addSection("Grossoch", {
            //     new juce::TextPropertyComponent{vMin, "Min value", INT_MAX, false},
            //     new juce::TextPropertyComponent{vMax, "Min value", INT_MAX, false},
            // }, true, 0, true);
            addProperties({
                new juce::TextPropertyComponent{vMin, "Min value", INT_MAX, false},
                new juce::TextPropertyComponent{vMax, "Max value", INT_MAX, false},
            });
        }

        ~ContinuousParameterConfig() override = default;

        // void resized() override
        // {
            // auto rect = getLocalBounds();
            // minValue.setBounds(rect.removeFromTop(30));
            // maxValue.setBounds(rect.removeFromTop(30));
        // }
    };
}
