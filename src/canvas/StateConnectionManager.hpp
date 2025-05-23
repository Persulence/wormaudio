#pragma once
#include <memory>

#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    class StateConnectionManager
    {
    public:
        using Point = juce::Point<float>;

    private:
        bool dragging{false};
        Point start;
        Point end;

        juce::Component* parent;

    public:
        using Ptr = std::shared_ptr<StateConnectionManager>;

        StateConnectionManager(juce::Component* parent);

        void startConnection(Point start);
        void updateConnection(Point end);
        void commitConnection(Point end);

        void paint(juce::Graphics& g) const;
    };


    template <typename From, typename To>
    juce::Point<To> convertPoint(juce::Point<From> point)
    {
        return {static_cast<To>(point.getX()), static_cast<To>(point.getY())};
    }
}
