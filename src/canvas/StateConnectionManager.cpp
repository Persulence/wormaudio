#include "StateConnectionManager.hpp"

namespace ui
{
    StateConnectionManager::StateConnectionManager(juce::Component *parent):
        parent(parent)
    {

    }

    void StateConnectionManager::startConnection(Point start)
    {
        dragging = true;
        this->start = start;
        this->end = start;
    }

    void StateConnectionManager::updateConnection(Point end)
    {
        this->end = end;

        parent->repaint();
    }

    void StateConnectionManager::commitConnection(Point end)
    {
        dragging = false;
        this->end = end;

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
