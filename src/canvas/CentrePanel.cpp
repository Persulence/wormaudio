#include "CentrePanel.hpp"

CentrePanel::CentrePanel():
        handle(ui::ResizeHandle(ui::ResizeHandle::Direction::HORIZONTAL, 500))
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
