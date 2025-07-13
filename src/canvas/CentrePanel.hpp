// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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

