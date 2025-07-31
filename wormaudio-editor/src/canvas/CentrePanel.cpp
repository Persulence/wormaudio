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

#include "CentrePanel.hpp"

using namespace ui;
using namespace juce;

CentrePanel::CentrePanel():
        // handle(ResizeHandle(ResizeHandle::Direction::HORIZONTAL, 500)),
        // canvasViewport(BorderPanel<CanvasViewport>{}),
        parameterPanel(BorderPanel<ParameterPanel>{}),
        editor(BorderPanel<BottomInspectorPanel>{*this}),
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

    editor::getInstance().onEventChanged.setup(&eventChangedListener, [this]
    {
        deselectAll();
    });
}

void CentrePanel::resized()
{
    std::vector<Component*> comps = {&parameterPanel, &bar1, &canvasViewport, &bar2, &editor};
    layout.layOutComponents(comps.data(), comps.size(), 0, 0, getWidth(), getHeight(), true, true);
    // canvasViewport->canvas.setBounds(getLocalBounds().expanded(500));
    // canvasViewport->setViewPosition(100, 100);
}
