#include "ComparisonCondition.hpp"

namespace event
{
    struct LogicTickInfo;
}

namespace condition
{
    void ComparisonCondition::setLeft(const Operand &operand)
    {
        // std::lock_guard guard{mutex};
        left = operand;
    }

    void ComparisonCondition::setRight(const Operand &operand)
    {
        // std::lock_guard guard{mutex};
        right = operand;
    }

    void ComparisonCondition::setOp(const Operator &op_)
    {
        // std::lock_guard guard{mutex};
        op = op_;
    }

    player::Sample ComparisonCondition::testImpl(const sm::ParameterLookup &pl, const event::LogicTickInfo &info, const sm::StateInstance &currentState) const
    {
        // std::lock_guard guard{mutex};
        return op(pl, left, right) ? 0 : -1;
    }
}
