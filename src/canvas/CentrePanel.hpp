#pragma once

#include <panel/BorderPanel.hpp>

#include "CanvasSelectionManager.hpp"
#include "CanvasViewport.hpp"
#include "BottomInspectorPanel.hpp"
#include "parameter/ParameterPanel.hpp"

namespace ui
{
    class CentrePanel : public ui::Panel, public CanvasSelectionManager
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

        void onSelect() override
        {
            editor->updateSelection();
        }

        void onDeselectAll() override
        {
            editor->updateSelection();
        }
    };
}

