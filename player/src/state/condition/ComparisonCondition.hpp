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
    // export auto DEFAULT_OPERAND{Operand{Operand::Value{ConstantOperand{0}}}};

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
        Operator op{Equal{}};

        // Fields will be accessible while events are running and inside the GUI
        // std::mutex mutex;

        FRIEND_CEREAL

        INTERNAL_SERIALIZE
        {
            // ar(left, right, op);
        }
    };

}
