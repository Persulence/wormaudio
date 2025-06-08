#pragma once

#include <utility>

#include "AutomationRegistry.hpp"
#include "Mapping.hpp"
#include "juce_core/juce_core.h"

namespace automation
{
    /**
     * Associates a property with a mapping.
     */
    class AutomationLink
    {
    public:
        AutomationLink(PropertyInstanceHandle property, const MappingFunction &mapping):
            property(std::move(property)),
            mapping(mapping) {}

    private:
        PropertyInstanceHandle property;
        MappingFunction mapping;
    };

    class AutomationTable : public AutomationRegistry
    {
    public:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AutomationTable)

        explicit AutomationTable()
        {

        }

    private:
        // std::unordered_map<Proper, Entry> automation;
        std::vector<AutomationLink> automation;
    };
}
