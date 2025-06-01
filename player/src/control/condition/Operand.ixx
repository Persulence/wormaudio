module;

#include <string>
#include <variant>
#include <format>

export module control:Operand;

import parameter;
import :ParameterLookup;

namespace condition
{
    export struct ParameterOperand
    {
        std::string paramName;

        ParameterValue operator()(const sm::ParameterLookup& lookup) const
        {
            return lookup.get(paramName).value;
        }

        std::string toString() const
        {
            return paramName;
        }
    };

    export struct ConstantOperand
    {
        ParameterValue value;

        ParameterValue operator()(const sm::ParameterLookup& lookup) const
        {
            return value;
        }

        std::string toString() const;
    };

    export struct Operand
    {
        using Value = std::variant<
            ParameterOperand,
            ConstantOperand>;

        Value value;

        constexpr Operand(Value value_): value(std::move(value_)) {}

        ParameterValue operator()(const sm::ParameterLookup& lookup) const
        {
            return std::visit([&lookup](auto& o){ return o(lookup); }, value);
        }

        std::string toString() const
        {
            return std::visit([](auto& o){ return o.toString(); }, value);
        }
    };

    // using Operand = std::variant<
    //     ParameterOperand,
    //     ConstantOperand
    // >;
}
