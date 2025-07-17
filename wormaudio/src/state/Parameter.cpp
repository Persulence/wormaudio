// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "Parameter.hpp"

#include <cassert>
#include <format>
#include <regex>
#include <variant>

namespace parameter
{
    const std::regex PARAMETER_REGEX{"[a-zA-Z][a-zA-Z0-9]*"};

    ParameterType ParameterType::get(const Type id_)
    {
        switch (id_)
        {
            case CONTINUOUS.type:
                return CONTINUOUS;
            case DISCRETE.type:
                return DISCRETE;
            case ENUM.type:
                return ENUM;
            default:
                return CONTINUOUS;
        }
    }

    bool isValidName(const std::string &name)
    {
        return regex_match(name, PARAMETER_REGEX);
    }

    ParameterValue parseValue(const std::string &text)
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
            return ParameterType::CONTINUOUS;
        }
        if (std::holds_alternative<DiscreteParameterDef>(def))
        {
            return ParameterType::DISCRETE;
        }
        if (std::holds_alternative<EnumParameterDef>(def))
        {
            return ParameterType::ENUM;
        }

        assert(false);
    }
}
