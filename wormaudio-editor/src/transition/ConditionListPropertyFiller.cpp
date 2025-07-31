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

#include "ConditionListPropertyFiller.hpp"

#include <variant>
#include <variant>
#include <variant>
#include <variant>
#include <variant>
#include <variant>

#include "panel/ChoicePropertyWidget.hpp"
#include "panel/MyPropertyPanel.hpp"
#include "state/condition/AllElementsDoneCondition.hpp"

namespace ui
{
    using namespace juce;
    using namespace sm;
    using namespace condition;

    ConditionListPropertyFiller::ConditionListPropertyFiller(ConditionList &conditionList_):
        conditionList(conditionList_)
    {
    }

    void ConditionListPropertyFiller::initProperties()
    {
        setHeader(std::make_unique<SectionHeader>("Condition List"));

        add(ChoicePropertyWidget<ConditionBoolOperator>::create("Operator",
            {
                {"OR", ConditionBoolOperator::OR},
                {"AND", ConditionBoolOperator::AND}
            }, &conditionList.op));

        // for (auto& condition : conditionList.conditions)
        for (int i = 0; i < conditionList.conditions.size(); i++)
        {
            auto& condition = conditionList.conditions.at(i);
            auto child = ConditionPropertyFiller::create(condition, i);
            add(std::shared_ptr(std::move(child)));
        }
    }

    void ConditionListPropertyFiller::mouseDown(const MouseEvent &event)
    {
        if (event.mods.isRightButtonDown())
        {
            PopupMenu menu;
            menu.addItem("New comparison condition", [this]
            {
                addCondition(ComparisonCondition{});
            });
            menu.addItem("New time condition", [this]
            {
                addCondition(TimeCondition{});
            });
            menu.addItem("New quantise condition", [this]
            {
                addCondition(QuantiseCondition{});
            });
            menu.addItem("New random condition", [this]
            {
                addCondition(RandomCondition{});
            });
            menu.addItem("All elements finished", [this]
            {
                addCondition(AllElementsDoneCondition{});
            });

            menu.showMenuAsync(PopupMenu::Options{});
        }
    }

    void ConditionListPropertyFiller::addCondition(Condition&& condition)
    {
        conditionList.insertCondition(std::move(condition));
        refresh();
    }

    void ConditionListPropertyFiller::removeConditionFiller(const int index)
    {
        conditionList.conditions.erase(conditionList.conditions.begin() + index);
        refresh();
    }
}
