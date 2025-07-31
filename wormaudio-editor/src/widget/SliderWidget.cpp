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

#include "SliderWidget.hpp"

namespace ui
{
    using namespace juce;

    SliderWidget::SliderWidget():
        label(parse::parseFloat)
    {
        addAndMakeVisible(label);
        label.addMouseListener(this, true);

        label.listen(&onChanged);
    }

    void SliderWidget::setRange(const Value min_, const Value max_, const Value increment_)
    {
        min = min_;
        max = max_;
        increment = increment_;
    }

    void SliderWidget::setValue(Value value, bool notify)
    {
        current = value;
        label.setTextParse(value);

        if (notify)
            onChanged.emit(current);
    }

    void SliderWidget::mouseDown(const juce::MouseEvent &event)
    {
        dragValue = current;

        if (event.mods.isRightButtonDown())
        {
            mouseDownValue(event);
        }
    }

    void SliderWidget::mouseDrag(const juce::MouseEvent &event)
    {
        const auto dx = event.getDistanceFromDragStartX();
        if (event.mods.isLeftButtonDown())
        {
            const Value sensitivity = 0.005;
            float range = std::abs(max - min);
            // event.source.enableUnboundedMouseMovement(true);
            snapValue(dragValue + range * sensitivity * dx);
        }
        else if (event.mods.isRightButtonDown())
        {
            mouseDownValue(event);
        }
    }

    void SliderWidget::mouseUp(const MouseEvent &event)
    {
        event.source.enableUnboundedMouseMovement(false);
    }

    void SliderWidget::mouseDownValue(const juce::MouseEvent &event)
    {
        const auto bounds = getLocalBounds();
        const double f = (event.x - bounds.getX()) / static_cast<double>(bounds.getWidth());
        snapValue(min + f * (max - min));
    }

    void SliderWidget::paint(juce::Graphics &g)
    {
        const Value f = (current - min) / (max - min);
        const auto bounds = getLocalBounds().toFloat().expanded(-0.5f);
        const auto rect = bounds.withWidth(f * getWidth());

        g.setColour(juce::Colours::red);
        g.fillRoundedRectangle(rect, 5);
        // g.setColour(juce::Colours::white);
        // auto w = getWidth();
        // g.drawText(juce::String{current}, getX(), getY(), getWidth(), getHeight(), juce::Justification::centred, true);

        g.setColour(juce::Colours::black);
        g.drawRoundedRectangle(bounds, 5, 1);
    }

    void SliderWidget::resized()
    {
        label.setBounds(getLocalBounds());
    }

    void SliderWidget::snapValue(Value value)
    {
        auto oldCurrent = current;
        if (increment > 0)
        {
            auto div = value / increment;
            auto rounded = std::round(div);
            current = std::clamp(rounded * increment, min, max);
        }
        else
        {
            if (min < max)
            {
                current = std::clamp(value, min, max);
            }
            else
            {
                current = std::clamp(value, max, min);
            }
        }

        if (current != oldCurrent)
        {
            // notify
            onChanged.emit(current);
            repaint();
        }
    }
}
