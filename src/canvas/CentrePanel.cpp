#include "CentrePanel.hpp"

using namespace ui;
using namespace juce;

CentrePanel::CentrePanel():
        // handle(ResizeHandle(ResizeHandle::Direction::HORIZONTAL, 500)),
        // canvasViewport(BorderPanel<CanvasViewport>{}),
        parameterPanel(BorderPanel<ParameterPanel>{}),
        editor(BorderPanel<StateEditorPanel>{*this}),
        bar1(&layout, 1, false),
        bar2(&layout, 3, false)
{
    addAndMakeVisible(parameterPanel);
    addAndMakeVisible(bar1);
    addAndMakeVisible(canvasViewport);
    addAndMakeVisible(bar2);
    addAndMakeVisible(editor);

    layout.setItemLayout(0, -0.1, -0.9, -0.1);
    layout.setItemLayout(1, 5, 5, 5);
    layout.setItemLayout(2, -0.1, -0.9, -0.65);
    layout.setItemLayout(3, 5, 5, 5);
    layout.setItemLayout(4, -0.1, -0.9, -0.25);
}

void CentrePanel::resized()
{
    std::vector<Component*> comps = {&parameterPanel, &bar1, &canvasViewport, &bar2, &editor};
    layout.layOutComponents(comps.data(), comps.size(), 0, 0, getWidth(), getHeight(), true, true);
    // canvasViewport->canvas.setBounds(getLocalBounds().expanded(500));
    // canvasViewport->setViewPosition(100, 100);
}
