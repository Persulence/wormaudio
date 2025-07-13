// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
