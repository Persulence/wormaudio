// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "GlobalParameterLookup.hpp"

#include <memory>
#include <unordered_map>

#include "../event/ParameterList.hpp"

namespace sm
{
    using namespace player;

    void GlobalParameterLookup::refresh(event::ParameterList &list)
    {
        std::unordered_map<std::string, std::unique_ptr<parameter::ParameterInstance>> newInstances;

// #ifdef DEBUG
        // std::cout << "Refreshing parameters\n";
// #endif
        for (auto& parameter : list.getParameters())
        {
            // Retain previous value if the parameter existed before
            ParameterValue value{};
            if (auto it = instances.find(parameter->getName()); it != instances.end())
                value = it->second->value;

            const auto instance = newInstances.emplace(parameter->getName(), std::make_unique<parameter::ParameterInstance>(parameter)).first;
            instance->second->value = value;
        }

        instances = std::move(newInstances);
    }
}
