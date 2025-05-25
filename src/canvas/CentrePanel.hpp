#pragma once

#include <panel/BorderPanel.hpp>

#include "CanvasSelectionManager.hpp"
#include "StateCanvasPanel.hpp"
#include "StateEditorPanel.hpp"
#include "../panel/ResizeHandle.hpp"

namespace ui
{
    class CentrePanel : public ui::Panel, public CanvasSelectionManager
    {
    public:
        // StateCanvasPanel canvas;
        // StateEditorPanel editor;
        ResizeHandle handle;

        BorderPanel<StateCanvasPanel> canvas;
        BorderPanel<StateEditorPanel> editor;

        CentrePanel();
        void resized() override;

        void onSelect() override
        {
            editor->updateSelection();
        }
    };
}

