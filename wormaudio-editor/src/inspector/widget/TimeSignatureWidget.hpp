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
#include "property/PropertyWidget.hpp"
#include "util/Data.hpp"
#include "util/Time.hpp"
#include "util/component/MyLabel.hpp"

namespace ui
{
    class TimeSignatureWidget : public PropertyMember, util::Data<player::TimeSignature>::Listener
    {
    public:
        explicit TimeSignatureWidget(util::Data<player::TimeSignature> timeSignature);

        int getDesiredHeight() const override;

        void resized() override;
        void paint(juce::Graphics &g) override;

        DISABLE_COPY(TimeSignatureWidget)
        DISABLE_MOVE(TimeSignatureWidget)

    protected:
        util::Data<player::TimeSignature> timeSignature;

        MyLabel<int> numerator;
        MyLabel<int> denominator;

        void update();
    };

    class TimeSignaturePropertyWidget : public PropertyWidget
    {
    public:
        TimeSignaturePropertyWidget(const std::string &label, const util::Data<player::TimeSignature> &timeSignature) :
            PropertyWidget(label), backing(timeSignature)
        {
            addAndMakeVisible(backing);
        }

    protected:
        void setContentBounds(juce::Rectangle<int> bounds) override
        {
            backing.setBounds(bounds);
        }

        TimeSignatureWidget backing;
    };
}
