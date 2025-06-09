#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "signal/Signal.hpp"
#include "ParameterConfigWidget.hpp"

import parameter;

namespace ui
{
    class ContinuousParameterConfig : public ParameterConfig
    {
        juce::Label minValue;
        juce::Label maxValue;
        parameter::ContinuousParameterDef &def;

    public:
        explicit ContinuousParameterConfig(parameter::ContinuousParameterDef& def_):
            def(def_)
        {
            addAndMakeVisible(minValue);
            minValue.setEditable(true);
            minValue.setText(juce::String{def_.min}, juce::dontSendNotification);
            minValue.onTextChange = [this]()
            {
                def.min = parameter::parseValue(minValue.getText().toStdString());
                onChange.emit();
            };

            addAndMakeVisible(maxValue);
            maxValue.setEditable(true);
            maxValue.setText(juce::String{def_.max}, juce::dontSendNotification);
            maxValue.onTextChange = [this]()
            {
                def.max = parameter::parseValue(maxValue.getText().toStdString());
                onChange.emit();
            };
        }

        ~ContinuousParameterConfig() override = default;

        void resized() override
        {
            auto rect = getLocalBounds();
            minValue.setBounds(rect.removeFromTop(30));
            maxValue.setBounds(rect.removeFromTop(30));
        }
    };

    struct ConfigComponentVisitor
    {
        std::unique_ptr<ParameterConfig> operator()(parameter::ContinuousParameterDef& def) const
        {
            return std::make_unique<ContinuousParameterConfig>(def);
        }

        std::unique_ptr<ParameterConfig> operator()(parameter::DiscreteParameterDef& def) const
        {
            // return std::make_unique<ContinuousParameterConfig>(def);
            throw std::exception{};
        }

        std::unique_ptr<ParameterConfig> operator()(parameter::EnumParameterDef& def) const
        {
            // return std::make_unique<ContinuousParameterConfig>(def);
            throw std::exception{};
        }
    };
}
