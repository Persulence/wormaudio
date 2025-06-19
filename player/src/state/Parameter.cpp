#include "Parameter.hpp"

#include <cassert>
#include <format>
#include <regex>
#include <variant>

namespace parameter
{
    const std::regex PARAMETER_REGEX{"[a-zA-Z][a-zA-Z0-9]*"};

    bool isValidName(const std::string &name)
    {
        return regex_match(name, PARAMETER_REGEX);
    }

    ParameterValue parameter::parseValue(const std::string &text)
    {
        try
        {
            return std::stof(text);
        }
        catch (std::exception e)
        {
            return 0;
        }
    }

    std::string toString(ParameterValue value)
    {
        return std::format("{:.2f}", value);
    }

    ParameterType getType(const ParameterDef& def)
    {
        if (std::holds_alternative<ContinuousParameterDef>(def))
        {
            return CONTINUOUS;
        }
        if (std::holds_alternative<DiscreteParameterDef>(def))
        {
            return DISCRETE;
        }
        if (std::holds_alternative<EnumParameterDef>(def))
        {
            return ENUM;
        }

        assert(false);
    }
}
