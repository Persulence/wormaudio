#pragma once
#include <memory>

#include "Automation.hpp"

using AutomationValue = float;

namespace automation
{
    class PropertyDef
    {
        PropertyName id;
        AutomationValue defaultValue{};
        Unit unit;
        // TODO: log scale and unit

    public:
        explicit PropertyDef(const PropertyName &id_, const AutomationValue defaultValue_, Unit unit_):
            id(id_),
            defaultValue(defaultValue_),
            unit(unit_)
        {

        }

        PropertyName getId() { return id; }
    };

    class PropertyInstance
    {
        std::shared_ptr<PropertyDef> def;
        AutomationValue value{};

    public:
        void setValue(AutomationValue value);
        [[nodiscard]] AutomationValue getValue() const;
    };
}