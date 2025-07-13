// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once
#include "property/PropertyWidget.hpp"
#include "widget/SliderWidget.hpp"

namespace ui
{
    class SliderPropertyWidget : public PropertyWidget
    {
    public:
        SliderWidget slider;

        explicit SliderPropertyWidget(const std::string &label) :
            PropertyWidget(label)
        {
            addAndMakeVisible(slider);
        }

    protected:
        void setContentBounds(juce::Rectangle<int> bounds) override
        {
            slider.setBounds(bounds);
        }
    };
}
