#include "StateConnectionManager.hpp"

#include "StateNodeWidget.hpp"

import control;

namespace ui
{
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

        g.setColour(Colours::green);
        for (const auto& from : *stateNodes)
        {
            for (const auto& transition : from->getState()->getTransitions())
            {
                if (const auto& to = stateToNode.find(transition.nextState); to != stateToNode.end())
                {
                    const auto line = Line(
                        convertPoint<int, float>(from->getBounds().getCentre()),
                        convertPoint<int, float>(to->second->getBounds().getCentre()));

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
