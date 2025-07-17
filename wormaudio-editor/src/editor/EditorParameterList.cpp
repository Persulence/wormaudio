// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
