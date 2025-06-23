#include "ConditionPropertyFiller.hpp"

#include "comparison/ComparisonConditionPropertyFiller.hpp"
#include "comparison/TimeConditionFiller.hpp"
#include "inspector/InspectorRoot.hpp"

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
    };

    std::unique_ptr<PropertyFiller> ConditionPropertyFiller::create(Condition &condition)
    {
        return std::visit(Visitor{}, condition);
    }
}
