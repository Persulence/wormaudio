// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
    class EventParameterLookup;
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

        [[nodiscard]] player::Sample testImpl(const sm::EventParameterLookup &pl, const event::LogicTickInfo &info,
                                              const sm::StateInstance &currentState) const;

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
