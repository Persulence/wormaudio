
// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "PropertyWidget.hpp"

namespace ui
{
    using namespace juce;

    PropertyWidget::PropertyWidget(std::string label_):
        label(label_)
    {
        labelWidth = PropertyWidget::getDesiredLabelWidth();

        addAndMakeVisible(labelComponent);
        labelComponent.setText(label, dontSendNotification);
    }

    float PropertyWidget::getDesiredLabelWidth() const
    {
        return labelComponent.getFont().getStringWidth(label) * 1.1;
    }

    void PropertyWidget::setLabelWidth(float labelWidth_)
    {
        labelWidth = labelWidth_;
    }

    void PropertyWidget::resized()
    {
        // labelComponent.setBounds(0, 0, labelWidth, getHeight());
        auto rect = getLocalBounds();
        labelComponent.setBounds(rect.removeFromLeft(labelWidth));

        // Padding?

        setContentBounds(rect);
    }

    void PropertyWidget::paint(Graphics &g)
    {
        float thickness = 1;
        const auto bounds = getLocalBounds().toFloat().expanded(-thickness / 2);
        g.setColour(Colours::black);
        g.drawRoundedRectangle(bounds, 5, thickness);
        g.drawVerticalLine(labelWidth, 0, getHeight());
    }
}