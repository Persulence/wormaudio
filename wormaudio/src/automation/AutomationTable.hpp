// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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

        void clear();

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
