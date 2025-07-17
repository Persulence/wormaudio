// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "AutomationRegistry.hpp"
#include "Mapping.hpp"
#include "juce_core/juce_core.h"
#include "state/Parameter.hpp"
#include "Property.hpp"

namespace automation
{
    /**
     * Associates a property with a mapping.
     */
    struct AutomationLink
    {
        parameter::Parameter parameter;
        Property property;
        MappingFunction mapping;

        INTERNAL_SERIALIZE
        {
            ar(parameter, property, mapping);
        }
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

        FRIEND_CEREAL

        INTERNAL_SERIALIZE
        {
            ar(
                cereal::base_class<AutomationRegistry>(this),
                cereal::make_nvp("links", links)
                );
        }
    };
}
