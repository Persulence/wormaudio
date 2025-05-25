#include "CentrePanel.hpp"

using namespace ui;

CentrePanel::CentrePanel():
        handle(ResizeHandle(ResizeHandle::Direction::HORIZONTAL, 500)),
        canvas(BorderPanel<StateCanvasPanel>{}),
        editor(BorderPanel<StateEditorPanel>{*this})
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
    juce::FlexBox box;
    box.flexDirection = juce::FlexBox::Direction::column;
    box.items.add(juce::FlexItem(canvas).withMinHeight(handle.currentPosition));
    box.items.add(handle.asFlexItem());
    box.items.add(juce::FlexItem(editor).withFlex(200));
    box.performLayout(getLocalBounds());
}
