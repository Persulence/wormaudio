#pragma once
#include <memory>

#include "Automation.hpp"

using AutomationValue = float;

namespace automation
{
    class PropertyDef
    {
        PropertyIdentifier id;
        AutomationValue defaultValue{};
        Unit unit;
        // TODO: log scale and unit

    public:
        explicit PropertyDef(const PropertyIdentifier &id_, const AutomationValue defaultValue_, Unit unit_):
            id(id_),
            defaultValue(defaultValue_),
            unit(unit_)
        {

        }

        PropertyIdentifier getId() { return id; }
    };

    class PropertyInstance
    {
        std::shared_ptr<PropertyDef> def;
        AutomationValue value{};

    public:
        void setValue(AutomationValue value);
        AutomationValue getValue() const;
    };
}