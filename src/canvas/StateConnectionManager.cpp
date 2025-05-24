#include "StateConnectionManager.hpp"

#include <ranges>

#include "StateNodeWidget.hpp"

import control;

namespace ui
{
    using namespace juce;

    StateConnectionManager::StateConnectionManager(std::vector<std::shared_ptr<StateNodeWidget>> *stateNodes,
                                                   std::unordered_map<std::shared_ptr<sm::State>, std::shared_ptr<StateNodeWidget>>& stateToNode):
        stateNodes(stateNodes),
        stateToNode(stateToNode),
        vBlank(juce::VBlankAttachment{this, [this]() { update(); }})
    {
        setInterceptsMouseClicks(false, false);
    }

    void StateConnectionManager::startConnection(Point start_)
    {
        draggingConnection = true;
        this->start = start_;
        this->end = start_;
    }

    void StateConnectionManager::updateConnection(Point end_)
    {
        this->end = end_;

        repaint();
    }

    void StateConnectionManager::commitConnection(Point end_)
    {
        draggingConnection = false;
        this->end = end_;

        repaint();
    }

    void StateConnectionManager::paint(juce::Graphics &g)
    {
        using namespace juce;

        if (draggingConnection)
        {
            auto globalPoint = convertPoint<int, float>(localPointToGlobal(getPosition()));
            auto line = Line(start - globalPoint, end - globalPoint);

            g.setColour(Colours::red);
            g.drawLine(line);
        }

        // Draw the transition lines
        g.setColour(Colours::green);
        for (const auto& fromNode : *stateNodes)
        {
            auto fromState = fromNode->getState();
            for (const auto& nextState : std::views::keys(fromState->getTransitions()))
            {
                if (const auto& to = stateToNode.find(nextState); to != stateToNode.end())
                {
                    Point startPoint = convertPoint<int, float>(fromNode->getBounds().getCentre());
                    Point endPoint = convertPoint<int, float>(to->second->getBounds().getCentre());

                    // Offset lines if there is a two-way transition
                    if (nextState->getTransitions().contains(fromState))
                    {
                        float offset = 20;

                        // Get normalised vector perpendicular to the line
                        auto vector = endPoint - startPoint;
                        auto perp = Point(vector.y, vector.x);
                        float len = sqrtf(perp.x * perp.x + perp.y * perp.y);
                        perp = (perp / len) * offset;

                        startPoint += perp;
                        endPoint += perp;
                    }

                    const auto line = Line(startPoint, endPoint);

                    g.drawLine(line);
                }
            }
        }
    }

    void StateConnectionManager::update()
    {
        if (draggingNode)
            repaint();
    }

    void StateConnectionManager::makeConnection(StateNodeWidget *from, StateNodeWidget *to)
    {
        const sm::Transition1 transition{{}, to->getState()};
        from->getState()->insertTransition(transition);
    }

    void StateConnectionManager::setDraggingNode(bool drag)
    {
        draggingNode = drag;
    }
}
