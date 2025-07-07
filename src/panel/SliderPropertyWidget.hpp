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
