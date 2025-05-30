#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "CanvasSelectionManager.hpp"
#include "StateNodeWidget.fwd.hpp"

namespace ui
{
    class TransitionArrowComponent : public juce::Component, public CanvasSelectionTarget, public std::enable_shared_from_this<TransitionArrowComponent>
    {
        std::weak_ptr<StateNodeWidget> from;
        std::weak_ptr<StateNodeWidget> to;

        bool selected{false};

    public:
        void setNodes(const StateNodeWidgetPtr &from, const StateNodeWidgetPtr &to);
        void updateBounds();

        void paint(juce::Graphics &g) override;

        bool hitTest(int x, int y) override;
        void mouseDown(const juce::MouseEvent &event) override;

        std::shared_ptr<Component> createConfig() override;
        void onSelect() override;
        void onDeselect() override;

    private:
        // juce::Colour getCol();
    };
}
