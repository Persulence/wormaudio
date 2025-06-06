module;

#include <variant>
#include <mutex>

export module sm:ComparisonCondition;

import :Condition;
import :ParameterLookup;
import :Operand;
import :Operator;

namespace condition
{
    // export auto DEFAULT_OPERAND{Operand{Operand::Value{ConstantOperand{0}}}};

    export class ComparisonCondition : public ConditionBase<ComparisonCondition>
    {
        Operand left{ConstantOperand{}};
        Operand right{ConstantOperand{}};
        Operator op{Equal{}};

        // Fields will be accessible while events are running and inside the GUI
        // std::mutex mutex;

    public:
        ComparisonCondition()
        {

        }

        void setLeft(const Operand &operand);
        void setRight(const Operand &operand);
        void setOp(const Operator &op);

        Operand getLeft() { return left; }
        Operand getRight() { return right; }
        Operator getOp() { return op; }

        [[nodiscard]] bool testImpl(const sm::ParameterLookup& pl) const;
    };

}

