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

#include "SpatialSelectorWidget.hpp"

#include "editor/Editor.hpp"
#include "util/GuiResources.hpp"

namespace ui
{
    using namespace juce;

    SpatialSelectorWidget::SpatialSelectorWidget()
    {
        sourcePos = getLocalBounds().getCentre().toFloat();

        // editor::getInstance().eventChanged.setup(this, [this]
        // {
        // });
    }

    void SpatialSelectorWidget::paint(juce::Graphics &g)
    {
        g.setColour(Colours::darkgrey);
        float thickness = 2;
        g.fillEllipse(thickness / 2, thickness / 2, diameter - thickness / 2, diameter - thickness / 2);
        g.setColour(Colours::lightgrey);
        g.drawEllipse(thickness / 2, thickness / 2, diameter - thickness / 2, diameter - thickness / 2, thickness);

        float iconW = 25;
        auto centre = getLocalBounds().getCentre().toFloat();
        auto absSourcePos = centre + (sourcePos * (diameter / 2));
        auto imageBounds = Rectangle{absSourcePos.x - iconW / 2, absSourcePos.y - iconW / 2, iconW, iconW};
        g.drawImage(getIcon("icon/speaker.png"), imageBounds, RectanglePlacement::fillDestination, false);
    }

    void SpatialSelectorWidget::resized()
    {
        diameter = std::min(getWidth(), getHeight());
    }

    void SpatialSelectorWidget::mouseDown(const juce::MouseEvent &event)
    {
        if (event.mods.isLeftButtonDown())
        {
            updatePosition(event.position);
        }
    }

    void SpatialSelectorWidget::mouseDrag(const juce::MouseEvent &event)
    {
        if (event.mods.isLeftButtonDown())
        {
            updatePosition(event.position);
        }
    }

    void SpatialSelectorWidget::mouseDoubleClick(const juce::MouseEvent &event)
    {
        updatePosition(getLocalBounds().getCentre().toFloat());
    }

    void SpatialSelectorWidget::updatePosition(juce::Point<float> point)
    {
        auto centre = getLocalBounds().getCentre().toFloat();

        auto vec = point - centre;
        vec /= (diameter / 2);

        auto length = std::sqrt(vec.x * vec.x + vec.y * vec.y);
        if (length < 1)
        {
            sourcePos = vec;
            setSoundPosition(vec.x, vec.y);
        }
        else
        {
            vec /= length;
            sourcePos = vec;
            setSoundPosition(vec.x, vec.y);
        }

        repaint();
    }

    void SpatialSelectorWidget::setSoundPosition(float x, float z)
    {
        instance::Vec3f vec{x, 0, z};

        auto& editor = editor::getInstance();
        auto event = editor.getEvent();

        vec *= event->getProperties().maxDistance;

        editor.getSoundInstance()->setPosition(vec);
    }
}
