// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once
#include "Parameter.hpp"

namespace parameter
{
    class ParameterLookup
    {
    public:
        virtual ~ParameterLookup() = default;

        virtual ParameterValue getValue(const std::string& name) const = 0;;
        virtual ParameterInstance& get(const Parameter& parameter) const = 0;
        virtual ParameterInstance& get(const std::string& name) const = 0;
    };
}
