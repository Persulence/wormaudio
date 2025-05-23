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
//        juce::DragAndDropContainer* dragAndDrop;

    public:
        using Ptr = std::shared_ptr<StateConnectionManager>;

        explicit StateConnectionManager(juce::Component *parent_);

        void startConnection(Point start_);
        void updateConnection(Point end_);
        void commitConnection(Point end_);

        void paint(juce::Graphics& g) const;
    };


    template <typename From, typename To>
    juce::Point<To> convertPoint(juce::Point<From> point)
    {
        return {static_cast<To>(point.getX()), static_cast<To>(point.getY())};
    }
}
