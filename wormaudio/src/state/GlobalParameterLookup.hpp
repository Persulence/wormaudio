// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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

        parameter::ParameterInstance* getChecked(std::string name)
        {
            if (const auto it = instances.find(name); it != instances.end())
            {
                return it->second.get();
            }

            return nullptr;
        }
    };
}
