// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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

