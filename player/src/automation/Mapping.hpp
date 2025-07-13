// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once
#include "Automation.hpp"
#include "cereal/access.hpp"
#include "util/serialization_util.hpp"

namespace automation
{
    class MappingFunction
    {
    public:
        MappingFunction() = default;

        AutomationValue operator()(const AutomationValue value) const
        {
            // TODO
            return value;
        }

    private:
        FRIEND_CEREAL

        INTERNAL_SERIALIZE
        {
        }
    };
}
