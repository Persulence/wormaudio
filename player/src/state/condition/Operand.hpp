#pragma once

#include <string>
#include <variant>
#include <format>

#include "state/ParameterLookup.hpp"

namespace condition
{
    struct ParameterOperand
    {
        std::string paramName;

        ParameterValue operator()(const sm::ParameterLookup& lookup) const
        {
            return lookup.getValue(paramName);
        }

        [[nodiscard]] std::string toString() const
        {
            return paramName;
        }
    };

    struct ConstantOperand
    {
        ParameterValue value;

        ParameterValue operator()(const sm::ParameterLookup& lookup) const
        {
            return value;
        }

        [[nodiscard]] std::string toString() const;
    };

    struct Operand
    {
        using Value = std::variant<
            ParameterOperand,
            ConstantOperand>;

        Value value;

        constexpr explicit Operand(Value value_): value(std::move(value_)) {}

        ParameterValue operator()(const sm::ParameterLookup& lookup) const
        {
            return std::visit([&lookup](auto& o){ return o(lookup); }, value);
        }

        [[nodiscard]] std::string toString() const
        {
            return std::visit([](auto& o){ return o.toString(); }, value);
        }
    };

    // using Operand = std::variant<
    //     ParameterOperand,
    //     ConstantOperand
    // >;
}
