// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "AutomationRegistryInstance.hpp"

#include "automation/Property.hpp"

namespace automation
{
    PropertyInstanceContainer::PropertyInstanceContainer(PropertyContainer container)
    {
        for (auto& prop : container.properties)
        {
            instances.push_back(PropertyInstanceHandle{std::make_shared<PropertyInstance>(prop)});
        }
    }
}
