#pragma once

#include "StateConnectionManager.hpp"
#include "../panel/Panel.hpp"

import control;

namespace sm
{
    class StateMachineDefinition;
}

namespace ui
{
    class StateNodeWidget;

    // class Occluder : public Panel
    // {
    // public:
    //     Occluder();
    //     void paint(juce::Graphics &g) override;
    // };

    class StateCanvasPanel : public Panel
    {
        std::vector<std::shared_ptr<StateNodeWidget>> stateNodes;
        std::unordered_map<std::shared_ptr<sm::State>, std::shared_ptr<StateNodeWidget>> stateToNode;
        StateConnectionManager::Ptr connectionManager{};

        // TODO: temporary
        std::shared_ptr<sm::StateMachineDefinition> definition;

    public:
        StateCanvasPanel();
        void addNode(const std::shared_ptr<StateNodeWidget>& node);
        void addNode();
        void removeNode(const std::shared_ptr<StateNodeWidget> &node);
        void paint(juce::Graphics &g) override;
        void mouseDown(const juce::MouseEvent &event) override;
        void resized() override;
    };

    class StateEditorPanel : public Panel
    {
    public:
        void paint(juce::Graphics &g) override;
    };
}
