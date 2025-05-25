#pragma once
#include <memory>

#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"

namespace sm {
    class State;
}

namespace ui
{
    class StateNodeWidget;

    class CanvasConnectionManager : public juce::Component
    {
    public:
        using Point = juce::Point<float>;

    private:
        bool draggingConnection{false};
        bool draggingNode{false};
        Point start;
        Point end;
        std::vector<std::shared_ptr<StateNodeWidget>>* stateNodes;
        std::unordered_map<std::shared_ptr<sm::State>, std::shared_ptr<StateNodeWidget>>& stateToNode;

        // juce::VBlankAttachment vBlank;

    public:
        using Ptr = std::shared_ptr<CanvasConnectionManager>;

        explicit CanvasConnectionManager(std::vector<std::shared_ptr<StateNodeWidget>>* stateNodes, std::unordered_map<std::shared_ptr<sm::State>, std::shared_ptr<StateNodeWidget>>& stateToNode);

        void startConnection(Point start_);
        void updateConnection(Point end_);
        void commitConnection(Point end_);
        static void makeConnection(StateNodeWidget* from, StateNodeWidget* to);

        void setDraggingNode(bool drag);

        void paint(juce::Graphics& g) override;

    private:
        void update();
    };


    template <typename From, typename To>
    juce::Point<To> convertPoint(juce::Point<From> point)
    {
        return {static_cast<To>(point.getX()), static_cast<To>(point.getY())};
    }
}

