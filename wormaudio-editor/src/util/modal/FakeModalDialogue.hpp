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

#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    /**
     * Covers the entire window. Holds the content component, which should be smaller.
     * Paints a drop shadow around the content.
     */
    class FakeModalDialogue : public juce::Component
    {
    public:
        std::shared_ptr<juce::Component> content;

        explicit FakeModalDialogue(std::shared_ptr<juce::Component> content);
        void paint(juce::Graphics &g) override;
        void paintOverChildren(juce::Graphics &g) override;
        void resized() override;

    private:
        juce::DropShadow dropShadow;
    };
}
