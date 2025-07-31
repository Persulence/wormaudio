// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "signal/Signal.hpp"
#include "util/component/MyLabel.hpp"

namespace ui
{
    class SliderWidget : public juce::Component
    {
        using Value = double;

        Value min{};
        Value max{1};
        Value current{};
        Value dragValue{};
        Value increment{};

        MyLabel<Value> label;

    public:
        using C = signal_event::Callback<Value>;
        C::Signal onChanged;

        SliderWidget();

        void setRange(Value min_, Value max_, Value increment_);
        void setValue(Value value, bool notify);

        void mouseDown(const juce::MouseEvent &event) override;
        void mouseDrag(const juce::MouseEvent &event) override;
        void mouseUp(const juce::MouseEvent &event) override;
        void paint(juce::Graphics &g) override;
        void resized() override;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SliderWidget)

    private:
        void mouseDownValue(const juce::MouseEvent& event);
        void snapValue(Value value);
    };
}
