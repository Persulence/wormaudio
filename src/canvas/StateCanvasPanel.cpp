#include "StateCanvasPanel.hpp"

using namespace juce;

namespace ui
{
    void StateCanvasPanel::paint(juce::Graphics &g)
    {
        paintBackground(g);
        paintBorder(g);
    }

    void StateEditorPanel::paint(juce::Graphics &g)
    {
        paintBackground(g);
        paintBorder(g);
    }

    CentrePanel::CentrePanel():
        handle(ResizeHandle(ResizeHandle::Direction::HORIZONTAL, 500))
    {
        addAndMakeVisible(canvas);
        addAndMakeVisible(editor);
        addAndMakeVisible(handle);

        handle.drag.emplace_back([this](float f) {
            resized();
        });
    }

    void CentrePanel::resized()
    {
        FlexBox box;
        box.flexDirection = FlexBox::Direction::column;
        box.items.add(FlexItem(canvas).withMinHeight(handle.currentPosition));
        box.items.add(handle.asFlexItem());
        box.items.add(FlexItem(editor).withFlex(200));
        box.performLayout(getLocalBounds());
    }
}
