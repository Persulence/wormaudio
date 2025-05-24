#pragma once

#include "CanvasSelectionManager.hpp"
#include "StateCanvasPanel.hpp"
#include "StateEditorPanel.hpp"
#include "../panel/ResizeHandle.hpp"

namespace ui
{
    class CentrePanel : public ui::Panel, public CanvasSelectionManager
    {
    public:
        StateCanvasPanel canvas;
        StateEditorPanel editor;
        ResizeHandle handle;

        CentrePanel();
        void resized() override;

        void onSelect() override
        {
            editor.updateSelection();
        }
    };
}

