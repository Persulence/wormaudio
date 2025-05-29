#include "CentrePanel.hpp"

using namespace ui;
using namespace juce;

CentrePanel::CentrePanel():
        // handle(ResizeHandle(ResizeHandle::Direction::HORIZONTAL, 500)),
        // canvasViewport(BorderPanel<CanvasViewport>{}),
        editor(BorderPanel<StateEditorPanel>{*this}),
        bar(&layout, 1, false)
{
    addAndMakeVisible(canvasViewport);
    addAndMakeVisible(editor);
    addAndMakeVisible(bar);

    layout.setItemLayout(0, -0.2, -0.9, -0.75);
    layout.setItemLayout(1, 5, 5, 5);
    layout.setItemLayout(2, -0.2, -0.9, -0.25);
}

void CentrePanel::resized()
{
    Component* comps[] = {&canvasViewport, &bar, &editor};
    layout.layOutComponents(comps, 3, 0, 0, getWidth(), getHeight(), true, true);
    // canvasViewport->canvas.setBounds(getLocalBounds().expanded(500));
    // canvasViewport->setViewPosition(100, 100);
}
