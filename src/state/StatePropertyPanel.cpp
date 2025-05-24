#include "StatePropertyPanel.hpp"

#include "canvas/StateNodeWidget.hpp"
#include "util/GuiUtil.hpp"

import ElementTypes;

namespace ui
{
    using namespace juce;

    void StatePropertyPanel::paint(juce::Graphics &g)
    {
        // if (auto shared = parent.lock())
        // {
        //     g.drawText(shared->getState()->getName(), getLocalBounds(), juce::Justification::centred, true);
        // }
    }

    void StatePropertyPanel::resized()
    {
        FlexBox box;
        box.flexDirection = FlexBox::Direction::column;
        box.flexWrap = FlexBox::Wrap::noWrap;

        for (const auto& element : elements)
        {
            box.items.add(FlexItem{*element}.withMinHeight(30).withMinWidth(getParentWidth()));
        }

        box.performLayout(getLocalBounds());
    }

    void StatePropertyPanel::mouseDown(const juce::MouseEvent &event)
    {
        using namespace element;

        if (event.mods.isRightButtonDown())
        {
            if (const auto shared = parent.lock())
            {
                shared->getState()->insertElement(std::make_shared<ClipElement>(nullptr));
                update();
                resized();
                repaint();
            }
        }
    }
}

