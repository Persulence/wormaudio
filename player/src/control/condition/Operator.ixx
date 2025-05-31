module;

#include <juce_core/juce_core.h>

export module control:Operator;

import :Operand;
import :ParameterLookup;

namespace condition
{
    #define DECLARE_OPERATOR_INFIX(Name, op) \
    export struct Name\
    {\
        bool operator()(const sm::ParameterLookup& lookup, const Operand& left, const Operand& right) const\
        {\
            return left(lookup) op right(lookup);\
        }\
    };

    #define DECLARE_OPERATOR_FUNC(Name, func) \
    export struct Name\
    {\
        bool operator()(const sm::ParameterLookup& lookup, const Operand& left, const Operand& right) const\
        {\
            return func(left(lookup), right(lookup));\
        }\
    };

    DECLARE_OPERATOR_FUNC(Equal, juce::approximatelyEqual)
    DECLARE_OPERATOR_FUNC(NotEqual, !juce::approximatelyEqual)
    DECLARE_OPERATOR_INFIX(Less, <)
    DECLARE_OPERATOR_INFIX(Greater, >)
    DECLARE_OPERATOR_INFIX(LessEqual, <=)
    DECLARE_OPERATOR_INFIX(GreaterEqual, >=)

    // struct Greater
    // {
    //     bool operator()(sm::ParameterLookup& lookup, Operand& left, Operand& right) const
    //     {
    //         return left(lookup) > right(lookup);
    //     }
    // };

    struct Operator
    {
        using Value = std::variant<
            Equal,
            NotEqual,
            Less,
            Greater,
            LessEqual,
            GreaterEqual
        >;

        Value value;

        bool operator()(const sm::ParameterLookup& lookup, const Operand& left, const Operand& right) const
        {
            return std::visit([&lookup, &left, &right](auto& o){ return o(lookup, left, right); }, value);
        }
    };
}
