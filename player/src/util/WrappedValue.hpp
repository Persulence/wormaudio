// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "juce_data_structures/juce_data_structures.h"

// namespace ui
// {
    template<typename T>
    struct ExplicitValue final : juce::Value::Listener
    {
        juce::Value backing;

        ExplicitValue()
        {
            // backing.addListener(this);
        }

        void valueChanged(juce::Value &value) override
        {
            // currentValue = static_cast<T>(value.getValue());
        }

        T operator*() const
        {
            // return currentValue;
            return  static_cast<T>(backing.getValue());
        }

        void operator=(const T& val)
        {
            backing.setValue(val);
        }

    private:
        // T currentValue{};
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
