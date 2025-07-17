// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "CanvasSelectionManager.hpp"
#include "StateNodeWidget.fwd.hpp"

namespace ui
{
    class TransitionArrowComponent : public juce::Component, public SelectionTarget, public std::enable_shared_from_this<TransitionArrowComponent>
    {
        std::weak_ptr<StateNodeWidget> from;
        std::weak_ptr<StateNodeWidget> to;

        bool selected{false};

    public:
        TransitionArrowComponent();
        void setNodes(const StateNodeWidgetPtr &from, const StateNodeWidgetPtr &to);
        std::tuple<StateNodeWidgetPtr, StateNodeWidgetPtr> lock() const;
        void updateBounds();

        void paint(juce::Graphics &g) override;

        bool hitTest(int x, int y) override;
        void mouseDown(const juce::MouseEvent &event) override;
        bool keyPressed(const juce::KeyPress &key) override;

        bool isTwoWay() const;
        bool isSelf() const;

        std::shared_ptr<Component> createConfig() override;
        void onSelect() override;
        void onDeselect() override;
    };
}
