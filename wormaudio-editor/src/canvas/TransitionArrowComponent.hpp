// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
