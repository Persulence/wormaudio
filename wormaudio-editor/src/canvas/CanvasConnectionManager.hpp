// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once
#include <memory>

#include "TransitionArrowComponent.hpp"
#include "command/SimpleCommandTarget.hpp"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"

namespace sm
{
    class StateDef;
}

namespace ui
{
    class StateNodeWidget;

    class CanvasConnectionManager : public juce::Component, public SimpleCommandTarget
    {
    public:
        using Point = juce::Point<float>;

    private:
        bool draggingConnection{false};
        bool draggingNode{false};

        Point start;
        Point end;

        std::vector<std::shared_ptr<StateNodeWidget>>* stateNodes;
        std::unordered_map<std::shared_ptr<sm::StateDef>, std::shared_ptr<StateNodeWidget>>& stateToNode;

        std::vector<std::shared_ptr<TransitionArrowComponent>> transitionWidgets;

        // juce::VBlankAttachment vBlank;

    public:
        using Ptr = std::shared_ptr<CanvasConnectionManager>;

        explicit CanvasConnectionManager(std::vector<std::shared_ptr<StateNodeWidget>>* stateNodes, std::unordered_map<std::shared_ptr<sm::StateDef>, std::shared_ptr<StateNodeWidget>>& stateToNode);

        void refreshTransitionWidgets();
        void updateTransitionWidgets() const;

        void startConnection(Point start_);
        void updateConnection(Point end_);
        void commitConnection(Point end_);
        void makeConnection(StateNodeWidget* from, StateNodeWidget* to);

        void setDraggingNode(bool drag);

        void paint(juce::Graphics& g) override;

        void removeTransition(const std::shared_ptr<TransitionArrowComponent> &component);
        void removeSelectedTransition();

    private:
        void update();

    };
}

