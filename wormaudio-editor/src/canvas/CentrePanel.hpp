// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include <panel/BorderPanel.hpp>

#include "CanvasSelectionManager.hpp"
#include "CanvasViewport.hpp"
#include "BottomInspectorPanel.hpp"
#include "InspectorSelectionManager.hpp"
#include "parameter/ParameterPanel.hpp"
#include "editor/Editor.fwd.hpp"

namespace ui
{
    class CentrePanel : public Panel, public CanvasSelectionManager
    {
    public:
        BorderPanel<ParameterPanel> parameterPanel;
        BorderPanel<CanvasViewport> canvasViewport;
        BorderPanel<BottomInspectorPanel> editor;

        juce::StretchableLayoutManager layout;
        juce::StretchableLayoutResizerBar bar1;
        juce::StretchableLayoutResizerBar bar2;

        CentrePanel();
        void resized() override;

    private:
        editor::EventChanged::Listener eventChangedListener;
    };
}

