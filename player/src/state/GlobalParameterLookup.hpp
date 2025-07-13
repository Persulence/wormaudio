// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <string>
#include <unordered_map>

#include "ParameterLookup.hpp"
#include "../event/ParameterList.hpp"
#include "util/Time.hpp"

namespace sm
{
    class GlobalParameterLookup : public parameter::ParameterLookup
    {
    public:
        std::unordered_map<std::string, std::unique_ptr<parameter::ParameterInstance>> instances;

        void refresh(event::ParameterList& list);

        ParameterValue getValue(const std::string& name) const override
        {
            if (const auto it = instances.find(name); it != instances.end())
            {
                return it->second->getValue();
            }

            return {};
        }

        parameter::ParameterInstance& get(const parameter::Parameter& parameter) const override
        {
            return get(parameter->getName());
        }

        parameter::ParameterInstance& get(const std::string& name) const override
        {
            return *instances.at(name);
        }
    };
}
