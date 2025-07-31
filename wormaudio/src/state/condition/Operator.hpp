// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include "juce_core/juce_core.h"

namespace condition
{
    // Using an enum instead of some elaborate variant nonsense
    enum class OperatorType : int
    {
        // EQUAL = '=',
        // NOT_EQUAL = '≠',
        // LESS = '<',
        // GREATER = '>',
        // LESS_EQUAL = '≤',
        // GREATER_EQUAL = '≥'
        EQUAL,
        NOT_EQUAL,
        LESS,
        GREATER,
        LESS_EQUAL,
        GREATER_EQUAL
    };

    inline bool applyOperatorType(const sm::EventParameterLookup& lookup, const OperatorType type, const Operand& left, const Operand& right)
    {
        switch (type)
        {
            case OperatorType::EQUAL:
                return juce::approximatelyEqual(left(lookup), right(lookup));
            case OperatorType::NOT_EQUAL:
                return !juce::approximatelyEqual(left(lookup), right(lookup));
            case OperatorType::LESS:
                return left(lookup) < right(lookup);
            case OperatorType::GREATER:
                return left(lookup) > right(lookup);
            case OperatorType::LESS_EQUAL:
                return left(lookup) <= right(lookup);
            case OperatorType::GREATER_EQUAL:
                return left(lookup) >= right(lookup);
        }
        return false;
    }

    constexpr std::string getOperatorSymbol(OperatorType type)
    {
        switch (type)
        {
            case OperatorType::EQUAL:
                return "=";
            case OperatorType::NOT_EQUAL:
                return "≠";
            case OperatorType::LESS:
                return "<";
            case OperatorType::GREATER:
                return ">";
            case OperatorType::LESS_EQUAL:
                return "≤";
            case OperatorType::GREATER_EQUAL:
                return "≥";
        }
        return "";
    }

    struct Operator
    {
        // using Value = std::variant<
        //     Equal,
        //     NotEqual,
        //     Less,
        //     Greater,
        //     LessEqual,
        //     GreaterEqual
        // >;

        // Value value;

        OperatorType op;

        constexpr std::string getSymbol() const
        {
            // return std::visit([](auto& o){ return o.getSymbol(); }, value);
            return getOperatorSymbol(op);
        }

        bool operator()(const sm::EventParameterLookup& lookup, const Operand& left, const Operand& right) const
        {
            // return std::visit([&lookup, &left, &right](auto& o){ return o(lookup, left, right); }, value);
            return applyOperatorType(lookup, op, left, right);
        }

        INTERNAL_SERIALIZE
        {
            ar(cereal::make_nvp("operator", op));
        }
    };
}
