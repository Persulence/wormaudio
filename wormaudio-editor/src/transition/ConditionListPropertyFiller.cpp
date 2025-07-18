// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
