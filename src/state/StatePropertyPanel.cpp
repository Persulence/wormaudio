#include "StatePropertyPanel.hpp"

#include "canvas/StateNodeWidget.hpp"
#include "util/GuiUtil.hpp"

#include "resource/ClipElement.hpp"

namespace ui
{
    using namespace juce;

    void StatePropertyPanel::paint(Graphics &g)
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
            box.items.add(FlexItem{*element}.withMinHeight(50).withMinWidth(getParentWidth()));
        }

        box.performLayout(getLocalBounds());
    }

    void StatePropertyPanel::mouseDown(const juce::MouseEvent &event)
    {
    }
}

