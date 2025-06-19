#include "ComparisonCondition.hpp"

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

    bool ComparisonCondition::testImpl(const sm::ParameterLookup &pl) const
    {
        // std::lock_guard guard{mutex};
        return op(pl, left, right);
    }
}
