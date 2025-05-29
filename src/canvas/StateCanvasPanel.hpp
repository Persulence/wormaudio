#pragma once

#include "StateNodeWidget.hpp"
#include "canvas/CanvasConnectionManager.hpp"
#include "../panel/Panel.hpp"

import control;

namespace sm
{
    class StateMachineDefinition;
}

namespace ui
{
    class StateNodeWidget;

    class StateCanvasPanel : public Panel
    {
        std::vector<std::shared_ptr<StateNodeWidget>> stateNodes;
        std::unordered_map<std::shared_ptr<sm::State>, std::shared_ptr<StateNodeWidget>> stateToNode;
        CanvasConnectionManager::Ptr connectionManager{};

        // TODO: temporary
        std::shared_ptr<sm::StateMachineDefinition> definition;

        std::weak_ptr<StateNodeWidget> selectedNode;

    public:
        StateCanvasPanel();

        StateNodeWidget::Ptr addNode(const std::shared_ptr<StateNodeWidget> &node);

        /// Creates a new state and adds a corresponding node
        StateNodeWidget::Ptr addState(juce::Point<int> pos);
        void removeNode(const std::shared_ptr<StateNodeWidget> &node);
        void paint(juce::Graphics &g) override;
        void mouseDown(const juce::MouseEvent &event) override;
        void resized() override;
        bool keyPressed(const juce::KeyPress &key) override;

        void contextMenu(juce::Point<int> mousePos);

        juce::Rectangle<int> calculateBounds() const;
    };
}
