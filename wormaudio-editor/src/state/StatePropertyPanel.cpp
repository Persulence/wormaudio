// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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

