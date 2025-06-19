#pragma once

#include "juce_data_structures/juce_data_structures.h"

// namespace ui
// {
    template<typename T>
    struct ExplicitValue final : juce::Value::Listener
    {
        T currentValue{};

        juce::Value backing;

        ExplicitValue()
        {
            backing.addListener(this);
        }

        void valueChanged(juce::Value &value) override
        {
            currentValue = static_cast<T>(value.getValue());
        }

        operator const T&()
        {
            return currentValue;
        }

        void operator=(const T& val)
        {
            backing.setValue(val);
        }
    };

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
