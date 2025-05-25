#include "CentrePanel.hpp"

using namespace ui;

CentrePanel::CentrePanel():
        // handle(ResizeHandle(ResizeHandle::Direction::HORIZONTAL, 500)),
        canvas(BorderPanel<StateCanvasPanel>{}),
        editor(BorderPanel<StateEditorPanel>{*this}),
        bar(&layout, 1, false)
{
    addAndMakeVisible(canvas);
    addAndMakeVisible(editor);
    // addAndMakeVisible(handle);
    addAndMakeVisible(bar);

    // handle.drag.emplace_back([this](float f) {
        // resized();
    // });

    layout.setItemLayout(0, -0.2, -0.9, -0.75);
    layout.setItemLayout(1, 5, 5, 5);
    layout.setItemLayout(2, -0.2, -0.9, -0.25);
}

void CentrePanel::resized()
{
    // juce::FlexBox box;
    // box.flexDirection = juce::FlexBox::Direction::column;
    // box.items.add(juce::FlexItem(canvas).withMinHeight(handle.currentPosition));
    // box.items.add(handle.asFlexItem());
    // box.items.add(juce::FlexItem(editor).withFlex(200));
    // box.performLayout(getLocalBounds());

    Component* comps[] = {&canvas, &bar, &editor};
    layout.layOutComponents(comps, 3, 0, 0, getWidth(), getHeight(), true, true);

}
