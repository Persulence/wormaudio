#pragma once

#include "juce_data_structures/juce_data_structures.h"

// namespace ui
// {
    struct WrappedValue : juce::Value::Listener
    {
        juce::Value value;
        std::function<void(juce::Value&)> callback = [](auto&){};

        WrappedValue()
        {
            value.addListener(this);
        }

        void valueChanged(juce::Value &value) override
        {
            callback(value);
        }

        explicit operator juce::Value&()
        {
            return value;
        }
    };
// }
