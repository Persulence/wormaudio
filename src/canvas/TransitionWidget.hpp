#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "CanvasSelectionManager.hpp"
#include "StateNodeWidget.fwd.hpp"

namespace ui
{
    class TransitionWidget : public juce::Component, public CanvasSelectionTarget
    {
        std::weak_ptr<StateNodeWidget> from;
        std::weak_ptr<StateNodeWidget> to;

    public:
        void setNodes(const StateNodeWidgetPtr &from, const StateNodeWidgetPtr &to);
        void updateBounds();

        void paint(juce::Graphics &g) override;

        void mouseDown(const juce::MouseEvent &event) override;

        std::shared_ptr<Component> createConfig() override;
        void onSelect() override;
        void onDeselect() override;
    };
}
