module;

#include <iostream>
#include <variant>

export module control:ComparisonCondition;

import :Condition;
import :ParameterLookup;
import :Operand;
import :Operator;

namespace condition
{
    // export auto DEFAULT_OPERAND{Operand{Operand::Value{ConstantOperand{0}}}};

    export struct ComparisonCondition : ConditionBase<ComparisonCondition>
    {
        Operand left{ConstantOperand{}};
        Operand right{ConstantOperand{}};
        Operator op{Equal{}};

        ComparisonCondition()
        {

        }

        [[nodiscard]] bool testImpl(const sm::ParameterLookup& pl) const
        {
            return op(pl, left, right);
        }
    };
}

