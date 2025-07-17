// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "ConditionPropertyFiller.hpp"

#include "comparison/ComparisonConditionPropertyFiller.hpp"
#include "../../inspector/filler/condition/TimeConditionFiller.hpp"
#include "inspector/InspectorRoot.hpp"
#include "inspector/filler/condition/AllElementsDoneConditionFiller.hpp"
#include "inspector/filler/condition/QuantiseConditionFiller.hpp"
#include "inspector/filler/condition/RandomConditionFiller.hpp"

namespace ui
{
    using namespace juce;
    using namespace condition;

    struct Visitor
    {

        std::unique_ptr<PropertyFiller> operator()(TimeCondition& condition) const
        {
            return std::make_unique<TimeConditionFiller>(condition);
        }

        std::unique_ptr<PropertyFiller> operator()(ComparisonCondition& condition) const
        {
            return std::make_unique<ComparisonConditionPropertyFiller>(condition);
        }

        std::unique_ptr<PropertyFiller> operator()(QuantiseCondition& condition) const
        {
            return std::make_unique<QuantiseConditionFiller>(condition);
        }

        std::unique_ptr<PropertyFiller> operator()(RandomCondition& condition) const
        {
            return std::make_unique<RandomConditionFiller>(condition);
        }

        std::unique_ptr<PropertyFiller> operator()(AllElementsDoneCondition& condition) const
        {
            return std::make_unique<AllElementsDoneConditionFiller>(condition);
        }
    };

    std::unique_ptr<PropertyFiller> ConditionPropertyFiller::create(Condition &condition)
    {
        return std::visit(Visitor{}, condition);
    }
}
