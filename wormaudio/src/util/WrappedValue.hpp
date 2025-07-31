// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
