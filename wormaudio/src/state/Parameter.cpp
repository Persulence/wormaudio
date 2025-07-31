// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
