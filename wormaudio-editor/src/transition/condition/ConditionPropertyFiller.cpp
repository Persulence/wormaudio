// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "ConditionPropertyFiller.hpp"

#include <variant>

#include "comparison/ComparisonConditionPropertyFiller.hpp"
#include "inspector/filler/condition/TimeConditionFiller.hpp"
#include "inspector/filler/condition/AllElementsDoneConditionFiller.hpp"
#include "inspector/filler/condition/QuantiseConditionFiller.hpp"
#include "inspector/filler/condition/RandomConditionFiller.hpp"
#include "transition/ConditionListPropertyFiller.hpp"

namespace ui
{
    using namespace juce;
    using namespace condition;

    struct Visitor
    {
        std::unique_ptr<PropertyFiller> operator()(TimeCondition& condition) const
        {
            return std::make_unique<TimeConditionFiller>(condition, index);
        }

        std::unique_ptr<PropertyFiller> operator()(ComparisonCondition& condition) const
        {
            return std::make_unique<ComparisonConditionPropertyFiller>(condition, index);
        }

        std::unique_ptr<PropertyFiller> operator()(QuantiseCondition& condition) const
        {
            return std::make_unique<QuantiseConditionFiller>(condition, index);
        }

        std::unique_ptr<PropertyFiller> operator()(RandomCondition& condition) const
        {
            return std::make_unique<RandomConditionFiller>(condition, index);
        }

        std::unique_ptr<PropertyFiller> operator()(AllElementsDoneCondition& condition) const
        {
            return std::make_unique<AllElementsDoneConditionFiller>(condition, index);
        }

        Visitor() = default;

        explicit Visitor(int index_): index(index_) {}

        int index;
    };

    std::unique_ptr<PropertyFiller> ConditionPropertyFiller::create(Condition &condition, const int index)
    {
        return std::visit(Visitor{index}, condition);
    }

    void ConditionPropertyFiller::mouseDown(const juce::MouseEvent &event)
    {
        if (event.mods.isRightButtonDown())
        {
            PopupMenu menu;

            menu.addItem("Delete", [this]
            {
                if (auto parent = findParentComponentOfClass<ConditionListPropertyFiller>())
                {
                    parent->removeConditionFiller(index);
                }
            });

            menu.showMenuAsync(PopupMenu::Options{});
        }
    }
}
