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
