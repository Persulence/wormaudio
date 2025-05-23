#pragma once

#include "../Panel.hpp"
#include "../panel/ResizeHandle.hpp"

namespace ui
{
    class StateNodeWidget;

    class StateCanvasPanel : public Panel
    {
        std::vector<std::shared_ptr<StateNodeWidget>> stateNodes;

    public:
        StateCanvasPanel();
        void addNode(std::shared_ptr<StateNodeWidget> node);
        void removeNode(std::shared_ptr<StateNodeWidget> node);
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
