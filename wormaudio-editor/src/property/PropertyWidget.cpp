
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