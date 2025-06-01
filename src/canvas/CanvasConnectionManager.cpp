#include "CanvasConnectionManager.hpp"

#include <ranges>

#include "StateNodeWidget.hpp"

import control;

namespace ui
{
    using namespace juce;

    CanvasConnectionManager::CanvasConnectionManager(std::vector<std::shared_ptr<StateNodeWidget>> *stateNodes,
                                                   std::unordered_map<std::shared_ptr<sm::State>, std::shared_ptr<StateNodeWidget>>& stateToNode):
        stateNodes(stateNodes),
        stateToNode(stateToNode)
        // vBlank(juce::VBlankAttachment{this, [this]() { update(); }})
    {
        setInterceptsMouseClicks(false, true);
    }

    void CanvasConnectionManager::refreshTransitionWidgets()
    {
        transitionWidgets.clear();
        removeAllChildren();

        for (const auto& fromNode : *stateNodes)
        {
            auto fromState = fromNode->getState();
            for (const auto& transition : std::views::values(fromState->getTransitions()))
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

        // Draw the transition lines
        // g.setColour(Colours::green);
        // for (const auto& fromNode : *stateNodes)
        // {
        // }
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

    // Causes stuttering when rendered with openGL
    void CanvasConnectionManager::update()
    {
        // if (draggingNode)
            // repaint();
    }

    void CanvasConnectionManager::makeConnection(StateNodeWidget *from, StateNodeWidget *to)
    {
        sm::Transition1::Ptr transition = std::make_shared<sm::Transition1>(condition::ConditionList{}, to->getState());
        transition->conditions.insertCondition(condition::ComparisonCondition{});
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
