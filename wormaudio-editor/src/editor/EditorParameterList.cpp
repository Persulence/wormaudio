// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "EditorParameterList.hpp"

namespace editor
{
    /**
     *
     * @return true if the parameter was renamed, false if not.
     */
    bool EditorParameterList::rename(const parameter::Parameter &parameter, const std::string &newName)
    {
        // Fail if the name would conflict with an existing parameter
        auto& parameters = target->parameters;

        if (const auto it = std::ranges::find_if(parameters, [newName](auto& p){ return p->getName() == newName; }); it != parameters.end())
        {
            // auto s = (*it)->getName();
            return false;
        }

        parameter->setName(newName);
        if (const auto it = std::ranges::find(parameters, parameter); it != parameters.end())
        {
            // Already present handling?
        }
        else
        {
            target->insert(parameter);
        }

        parameter->setName(newName);

        changed.emit();
        return true;
    }
}
