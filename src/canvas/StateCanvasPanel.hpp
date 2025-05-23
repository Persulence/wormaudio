#pragma once

#include "../Panel.hpp"

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

        CentrePanel();
        void resized() override;
    };
}
