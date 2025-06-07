#pragma once
#include <unordered_map>

#include "Automation.hpp"

namespace automation
{
    class AutomationRegistry
    {
    public:
        // Exposes the property for automation
        void reg(Property property);
        virtual ~AutomationRegistry() = default;

    protected:
        std::unordered_map<PropertyIdentifier, Property> registry;
    };
}
