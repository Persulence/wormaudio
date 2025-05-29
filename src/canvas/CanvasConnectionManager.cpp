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
        setInterceptsMouseClicks(false, false);
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
        g.setColour(Colours::green);
        for (const auto& fromNode : *stateNodes)
        {
            auto fromState = fromNode->getState();
            for (const auto& transition : std::views::values(fromState->getTransitions()))
            {
                if (auto shared = transition.nextState.lock())
                {
                    if (const auto& to = stateToNode.find(shared); to != stateToNode.end())
                    {
                        // Point startPoint = getLocalPoint(fromNode.get(), fromNode->getBounds().getCentre().toFloat());
                        Point startPoint = getLocalPoint(fromNode.get(), fromNode->getLocalBounds().getCentre().toFloat());
                        Point endPoint = getLocalPoint(to->second.get(), to->second->getLocalBounds().getCentre().toFloat());

                        auto vector = endPoint - startPoint;
                        float len = sqrtf(vector.x * vector.x + vector.y * vector.y);

                        // Skip unnecessarily short lines and divide by zeros
                        if (len <= 1)
                            continue;

                        // Offset lines if there is a two-way transition
                        if (shared->getTransitions().contains(fromState.get()))
                        {
                            float offset = 20;

                            // Get normalised vector perpendicular to the line
                            auto perp = Point(vector.y, -vector.x);
                            perp = (perp / len) * offset;

                            startPoint += perp;
                            endPoint += perp;
                        }

                        auto vector1 = endPoint - startPoint;
                        const auto line1 = Line(startPoint, startPoint + vector1 / 2);
                        const auto line2 = Line(startPoint + vector1 / 2, endPoint);

                        float thickness = 2;
                        float arrowSize = 15;
                        g.drawArrow(line1, thickness, arrowSize, arrowSize);
                        g.drawLine(line2, thickness);
                    }
                }
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
        sm::Transition1 transition{{}, to->getState()};
        transition.conditions.insertCondition(sm::TrueCondition{});
        from->getState()->insertTransition(transition);
    }

    void CanvasConnectionManager::setDraggingNode(bool drag)
    {
        draggingNode = drag;
        if (drag)
            repaint();
    }
}
