#pragma once

#include "StateCanvasPanel.hpp"
#include "../panel/ResizeHandle.hpp"

class CentrePanel : public ui::Panel
{
public:
    ui::StateCanvasPanel canvas;
    ui::StateEditorPanel editor;
    ui::ResizeHandle handle;

    CentrePanel();
    void resized() override;
};
