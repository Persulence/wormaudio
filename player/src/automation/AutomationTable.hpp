#pragma once

#include <unordered_map>
#include "automation.hpp"
#include "juce_core/juce_core.h"

namespace automation
{
    class AutomationTable
    {
    public:
        struct Entry;

        explicit AutomationTable():
            automation({}),
            registry({}) {}

        // Exposes the property for automation
        void reg(PropertyIdentifier id, Property property);

        

    private:
        std::unordered_map<juce::Identifier, Entry> automation;
        std::unordered_map<PropertyIdentifier, Property> registry;
    };
}
