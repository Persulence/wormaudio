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

#include "RandomConditionFiller.hpp"

#include "transition/condition/ConditionPropertyFiller.hpp"
#include "panel/MyPropertyPanel.hpp"

namespace ui
{
    RandomConditionFiller::RandomConditionFiller(condition::RandomCondition &condition_, int index):
        ConditionPropertyFiller(index),
        condition(condition_) {}

    void RandomConditionFiller::initProperties()
    {
        setHeader(std::make_unique<SectionHeader>("Random"));

        add(std::make_unique<DataEntryPropertyWidget<float>>("Chance", condition.chance, parse::parseFloat));
    }
}
