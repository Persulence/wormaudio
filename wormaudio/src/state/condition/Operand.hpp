// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include <string>
#include <variant>

#include "state/EventParameterLookup.hpp"

namespace condition
{
    struct ParameterOperand
    {
        std::string paramName;

        ParameterValue operator()(const sm::EventParameterLookup& lookup) const
        {
            return lookup.getValue(paramName);
        }

        [[nodiscard]] std::string toString() const
        {
            return paramName;
        }

        INTERNAL_SERIALIZE
        {
            ar(cereal::make_nvp("paramName", paramName));
        }
    };

    struct ConstantOperand
    {
        ParameterValue value;

        ParameterValue operator()(const sm::EventParameterLookup& lookup) const
        {
            return value;
        }

        [[nodiscard]] std::string toString() const;

        INTERNAL_SERIALIZE
        {
            ar(cereal::make_nvp("value", value));
        }
    };

    struct Operand
    {
        using Value = std::variant<
            ParameterOperand,
            ConstantOperand>;

        Value value;

        constexpr explicit Operand(Value value_): value(std::move(value_)) {}

        ParameterValue operator()(const sm::EventParameterLookup& lookup) const
        {
            return std::visit([&lookup](auto& o){ return o(lookup); }, value);
        }

        [[nodiscard]] std::string toString() const
        {
            return std::visit([](auto& o){ return o.toString(); }, value);
        }

        INTERNAL_SERIALIZE
        {
            ar(cereal::make_nvp("value", value));
        }
    };
}
