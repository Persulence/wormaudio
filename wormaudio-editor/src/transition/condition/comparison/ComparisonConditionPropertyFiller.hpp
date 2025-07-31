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

#include "ComparisonComboBox.hpp"
#include "../ConditionPropertyFiller.hpp"
#include "state/condition/ComparisonCondition.hpp"

namespace ui
{
    class ComparisonPropertyWidget : public PropertyMember, juce::ComboBox::Listener
    {
        condition::ComparisonCondition& condition;

        ComparisonComboBox left;
        ComparisonComboBox right;
        ComparisonComboBox op;

        juce::StretchableLayoutManager layout;

    public:
        explicit ComparisonPropertyWidget(condition::ComparisonCondition& condition_);

        int getDesiredHeight() const override
        {
            return settings::browserEntryHeight;
        }

        void comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged) override;

        void refresh();

        void resized() override;
    };

    class ComparisonConditionPropertyFiller : public ConditionPropertyFiller
    {

    public:
        ComparisonConditionPropertyFiller(condition::ComparisonCondition &condition_, int index);

        void initProperties() override;

        condition::ComparisonCondition &condition;
    };
}
