#include "StateConnectionManager.hpp"

namespace ui
{
    StateConnectionManager::StateConnectionManager(juce::Component *parent_) :
        parent(parent_)
    {

    }

    void StateConnectionManager::startConnection(Point start_)
    {
        dragging = true;
        this->start = start_;
        this->end = start_;
    }

    void StateConnectionManager::updateConnection(Point end_)
    {
        this->end = end_;

        parent->repaint();
    }

    void StateConnectionManager::commitConnection(Point end_)
    {
        dragging = false;
        this->end = end_;

        parent->repaint();
    }

    void StateConnectionManager::paint(juce::Graphics &g) const
    {
        using namespace juce;

        if (dragging)
        {
            auto globalPoint = convertPoint<int, float>(parent->localPointToGlobal(parent->getPosition()));
            auto line = Line(start - globalPoint, end - globalPoint);

            g.setColour(Colours::red);
            g.drawLine(line);
        }
    }
}
