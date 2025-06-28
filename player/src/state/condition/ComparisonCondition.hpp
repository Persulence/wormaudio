#pragma once

#include <variant>

#include "Condition.hpp"
#include "Operand.hpp"
#include "Operator.hpp"

namespace event
{
    struct LogicTickInfo;
}

namespace sm
{
    class ParameterLookup;
}

namespace condition
{
    class ComparisonCondition : public ConditionBase<ComparisonCondition>
    {
    public:
        ComparisonCondition() = default;

        void setLeft(const Operand &operand);

        void setRight(const Operand &operand);

        void setOp(const Operator &op);

        Operand getLeft() { return left; }
        Operand getRight() { return right; }
        Operator getOp() { return op; }

        [[nodiscard]] size_t testImpl(const sm::ParameterLookup &pl, const event::LogicTickInfo &info) const;

    private:
        Operand left{ConstantOperand{}};
        Operand right{ConstantOperand{}};
        Operator op{OperatorType::EQUAL};

        // Fields will be accessible while events are running and inside the GUI
        // std::mutex mutex;

        FRIEND_CEREAL

        INTERNAL_SERIALIZE
        {
            ar(CEREAL_NVP(left), CEREAL_NVP(right), CEREAL_NVP(op));
        }
    };

}
