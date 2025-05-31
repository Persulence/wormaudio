#pragma once

#include <panel/BorderPanel.hpp>

#include "CanvasSelectionManager.hpp"
#include "CanvasViewport.hpp"
#include "StateEditorPanel.hpp"

namespace ui
{
    class CentrePanel : public ui::Panel, public CanvasSelectionManager
    {
    public:
        BorderPanel<CanvasViewport> canvasViewport;
        BorderPanel<StateEditorPanel> editor;

        juce::StretchableLayoutManager layout;
        juce::StretchableLayoutResizerBar bar;

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

