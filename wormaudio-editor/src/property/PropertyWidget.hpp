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
#include "settings/settings.hpp"

namespace ui
{
    class PropertyMember : public juce::Component
    {
    public:
        enum RefreshLevel
        {
            /// This member should be reinitialised.
            SOFT,

            /// This member should be completely reconstructed by the parent member.
            HARD
        };

        virtual int getDesiredHeight() const = 0;
        virtual float getDesiredLabelWidth() const { return 0; };
        virtual void setLabelWidth(float labelWidth_) { }
    };

    class PropertyWidget : public PropertyMember
    {
    public:
        explicit PropertyWidget(std::string label);
        [[nodiscard]] float getDesiredLabelWidth() const override;
        void setLabelWidth(float labelWidth_) override;

        [[nodiscard]] int getDesiredHeight() const override { return settings::browserEntryHeight; }

        void resized() override;
        void paint(juce::Graphics &g) override;

    protected:
        virtual void setContentBounds(juce::Rectangle<int> bounds) = 0;

    private:
        std::string label;
        float labelWidth;

        juce::Label labelComponent;
    };
}
