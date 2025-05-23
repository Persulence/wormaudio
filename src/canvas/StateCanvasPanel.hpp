#pragma once

#include "../Panel.hpp"
#include "../panel/ResizeHandle.hpp"

namespace ui
{
    class StateCanvasPanel : public Panel
    {
    public:
        void paint(juce::Graphics &g) override;
    };

    class StateEditorPanel : public Panel
    {
    public:
        void paint(juce::Graphics &g) override;
    };

    class CentrePanel : public Panel
    {
    public:
        StateCanvasPanel canvas;
        StateEditorPanel editor;
        ResizeHandle handle;

        CentrePanel();
        void resized() override;
    };
}
