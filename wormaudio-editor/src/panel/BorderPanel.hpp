// Copyright (c)  2025 Thomas Paley-Menzies
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

#include "juce_gui_basics/juce_gui_basics.h"
#include "panel/Panel.hpp"

namespace ui
{
    template<typename Child> requires std::convertible_to<Child&, juce::Component&>
    class BorderPanel : public juce::Component
    {
        float borderWidth{1};

    public:
        Child child;

        template <typename... Args>
        explicit BorderPanel(Args&&... args):
            child(Child{std::forward<Args>(args)...})
        {
            addAndMakeVisible(child);
        }

        BorderPanel():
            child(Child{})
        {
            addAndMakeVisible(child);
        }

        Child* operator->() noexcept
        {
            return &child;
        }

        void resized() override
        {
            auto bounds = getLocalBounds();
            bounds.reduce(borderWidth, borderWidth);
            child.setBounds(bounds);
        }

        void paint(juce::Graphics &g) override
        {
            Panel::paintBorder(g, getLocalBounds(), borderWidth);
            // g.drawRect(getLocalBounds(), borderWidth);
        }
    };
}
