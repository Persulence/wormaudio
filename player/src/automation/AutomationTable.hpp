#pragma once

#include "AutomationRegistry.hpp"
#include "Mapping.hpp"
#include "juce_core/juce_core.h"
#include "state/Parameter.hpp"

namespace automation
{
    /**
     * Associates a property with a mapping.
     */
    struct AutomationLink
    {
    // public:
    //     AutomationLink(PropertyInstanceHandle property, const MappingFunction &mapping):
    //         property(std::move(property)),
    //         mapping(mapping) {}
    //
    // private:

        parameter::Parameter parameter;
        Property property;
        MappingFunction mapping;
    };

    class AutomationTable : public AutomationRegistry
    {
    public:
        JUCE_DECLARE_NON_COPYABLE(AutomationTable)

        explicit AutomationTable()
        {

        }

        void setup(const AutomationLink& link);

        const std::vector<AutomationLink>& getLinks() const { return links; }

    private:
        // std::unordered_map<Proper, Entry> automation;
        std::vector<AutomationLink> links;
    };
}
