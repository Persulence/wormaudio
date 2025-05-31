module;

#include <string>
#include <variant>

export module control:Operand;

import Parameter;
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
    };

    export struct ConstantOperand
    {
        ParameterValue value;

        ParameterValue operator()(const sm::ParameterLookup& lookup) const
        {
            return value;
        }
    };

    struct Operand
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
    };

    // using Operand = std::variant<
    //     ParameterOperand,
    //     ConstantOperand
    // >;
}
