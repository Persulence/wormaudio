// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "StatePropertyPanel.hpp"

#include "canvas/StateNodeWidget.hpp"
#include "util/GuiUtil.hpp"

namespace ui
{
    using namespace juce;

    void StatePropertyPanel::paint(juce::Graphics& g)
    {
        paintBackground(g);
    }

    void StatePropertyPanel::resized()
    {
        FlexBox box;
        box.flexDirection = FlexBox::Direction::column;
        box.flexWrap = FlexBox::Wrap::noWrap;

        for (const auto& element : elements)
        {
            box.items.add(FlexItem{*element}.withMinHeight(50).withMinWidth(getParentWidth()));
        }

        box.performLayout(getLocalBounds());
    }

    void StatePropertyPanel::mouseDown(const juce::MouseEvent &event)
    {
    }

    void StatePropertyPanel::update()
    {
        elements.clear();
        removeAllChildren();

        if (const auto shared = parent.lock())
        {
            for (auto& element : shared->getState()->getElements())
            {
                auto& widget = elements.emplace_back(std::make_shared<ElementRegionWidget>(element));
                addAndMakeVisible(*widget);
            }
        }
    }

    void StatePropertyPanel::removeElement(const resource::Handle<element::Element> &element)
    {
        if (auto node = parent.lock())
        {
            node->getState()->removeElement(element);
            update();
            resized();
            repaint();
        }
    }
}

