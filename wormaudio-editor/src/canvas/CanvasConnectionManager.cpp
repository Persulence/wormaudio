// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "CanvasConnectionManager.hpp"

#include <ranges>

#include "InspectorSelectionManager.hpp"
#include "StateNodeWidget.hpp"
#include "state/ConditionList.hpp"

namespace ui
{
    using namespace juce;

    CanvasConnectionManager::CanvasConnectionManager(std::vector<std::shared_ptr<StateNodeWidget>> *stateNodes,
                                                   std::unordered_map<std::shared_ptr<sm::StateDef>, std::shared_ptr<StateNodeWidget>>& stateToNode):
        stateNodes(stateNodes),
        stateToNode(stateToNode)
        // vBlank(juce::VBlankAttachment{this, [this]() { update(); }})
    {
        setInterceptsMouseClicks(false, true);

        commands()
            .add({Commands::DEL, [this](auto&){ removeSelectedTransition(); }})
            .finish();

        Commands::getInstance().getKeyMappings()->addKeyPress(Commands::DEL.id, KeyPress{KeyPress::deleteKey});
    }

    void CanvasConnectionManager::refreshTransitionWidgets()
    {
        transitionWidgets.clear();
        removeAllChildren();

        for (const auto& fromNode : *stateNodes)
        {
            auto fromState = fromNode->getState();
            for (const auto& transition : fromState->getTransitions())
            {
                if (auto shared = transition->nextState.lock())
                {
                    if (const auto& to = stateToNode.find(shared); to != stateToNode.end())
                    {
                        const auto& transitionWidget = transitionWidgets.emplace_back(std::make_shared<TransitionArrowComponent>());
                        addAndMakeVisible(transitionWidget.get());
                        transitionWidget->setNodes(fromNode, to->second);
                    }
                }
            }
        }
    }

    void CanvasConnectionManager::updateTransitionWidgets() const
    {
        for (const auto& widget : transitionWidgets)
        {
            widget->updateBounds();
        }
    }

    void CanvasConnectionManager::startConnection(Point start_)
    {
        draggingConnection = true;
        this->start = start_;
        this->end = start_;
    }

    void CanvasConnectionManager::updateConnection(Point end_)
    {
        this->end = end_;

        repaint();
    }

    void CanvasConnectionManager::commitConnection(Point end_)
    {
        draggingConnection = false;
        this->end = end_;

        repaint();
        // updateConnectionWidgets();
    }

    void CanvasConnectionManager::paint(Graphics &g)
    {
        using namespace juce;

        if (draggingConnection)
        {
            auto globalPoint = localPointToGlobal(getPosition()).toFloat();
            auto line = Line(start - globalPoint, end - globalPoint);

            g.setColour(Colours::red);
            g.drawLine(line);
        }
    }

    void CanvasConnectionManager::removeTransition(const std::shared_ptr<TransitionArrowComponent> &component)
    {
        transitionWidgets.erase(std::ranges::find(transitionWidgets, component));
        if (const auto [sharedFrom, sharedTo] = component->lock(); sharedFrom && sharedTo)
        {
            sharedFrom->getState()->removeTransitionTo(sharedTo->getState().get());
        }

        if (auto manager =findParentComponentOfClass<CanvasSelectionManager>(); manager)
        {
            manager->deselectAll();
        }
    }

    void CanvasConnectionManager::removeSelectedTransition()
    {
        auto manager = findParentComponentOfClass<InspectorSelectionManager>();
        if (manager)
        {
            if (auto shared = manager->getCurrent<TransitionArrowComponent>())
            {
                removeTransition(shared);
                manager->deselectAll();
            }
        }
    }

    // Causes stuttering when rendered with openGL
    void CanvasConnectionManager::update()
    {
        // if (draggingNode)
            // repaint();
    }

    void CanvasConnectionManager::makeConnection(StateNodeWidget *from, StateNodeWidget *to)
    {
        sm::Transition1::Ptr transition = std::make_shared<sm::Transition1>(std::make_unique<condition::ConditionList>(), to->getState());
        // transition->conditions->insertCondition(condition::ComparisonCondition{});
        from->getState()->insertTransition(transition);

        refreshTransitionWidgets();
    }

    void CanvasConnectionManager::setDraggingNode(bool drag)
    {
        draggingNode = drag;
        if (drag)
        {
            updateTransitionWidgets();
            // repaint();
        }
    }
}
