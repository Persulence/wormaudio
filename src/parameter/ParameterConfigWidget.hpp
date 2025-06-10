#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "signal/Signal.hpp"

namespace ui
{
    struct WrappedValue : juce::Value::Listener
    {
        juce::Value value;
        std::function<void(juce::Value&)> callback{};

        WrappedValue()
        {
            value.addListener(this);
        }

        void valueChanged(juce::Value &value) override
        {
            callback(value);
        }

        operator juce::Value&()
        {
            return value;
        }
    };

    class ParameterConfig : public juce::PropertyPanel
    {
    public:
        using OnChange = signal_event::Callback<>;
        OnChange::Signal onChange;
    };

}
