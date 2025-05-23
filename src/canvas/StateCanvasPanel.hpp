#pragma once

#include "StateConnectionManager.hpp"
#include "../Panel.hpp"
#include "../panel/ResizeHandle.hpp"

namespace ui
{
    class StateNodeWidget;

    class StateCanvasPanel : public Panel
    {
        std::vector<std::shared_ptr<StateNodeWidget>> stateNodes;
        StateConnectionManager::Ptr connectionManager{};

    public:
        StateCanvasPanel();
        void addNode(const std::shared_ptr<StateNodeWidget>& node);
        void addNode();
        void removeNode(const std::shared_ptr<StateNodeWidget> &node);
        void paint(juce::Graphics &g) override;
        void mouseDown(const juce::MouseEvent &event) override;
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
