#include "AutomationTable.hpp"
#include "Mapping.hpp"
#include "Property.hpp"

namespace automation
{
    struct AutomationTable::Entry
    {
        PropertyInstanceHandle property;
        MappingFunction mapping;
    };

    // void AutomationTable::insertEntry(juce::Identifier id, Entry &entry)
    // {
    //     entries.emplace(id, entry);
    // }

    void AutomationTable::reg(PropertyIdentifier id, Property property)
    {
        registry.emplace(id, property);
    }
}
