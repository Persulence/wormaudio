// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "RandomConditionFiller.hpp"

#include "panel/MyPropertyPanel.hpp"

namespace ui
{
    RandomConditionFiller::RandomConditionFiller(condition::RandomCondition &condition_):
        condition(condition_)
    {

    }

    void RandomConditionFiller::initProperties()
    {
        setHeader(std::make_unique<SectionHeader>("Random"));

        add(std::make_unique<DataEntryPropertyWidget<float>>("Chance", condition.chance, parse::parseFloat));
    }
}
