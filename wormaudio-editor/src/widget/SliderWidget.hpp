// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
