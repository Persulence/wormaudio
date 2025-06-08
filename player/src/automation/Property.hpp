#pragma once
#include <memory>
#include <bits/stl_vector.h>

#include "Automation.hpp"
#include "juce_core/system/juce_PlatformDefs.h"

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

        PropertyName getId() const{ return id; }

        AutomationValue getDefault() const{ return defaultValue; }
    };

    class PropertyInstance
    {
        std::shared_ptr<PropertyDef> def;
        AutomationValue value{};

    public:
        JUCE_DECLARE_NON_COPYABLE(PropertyInstance)

        explicit PropertyInstance(const std::shared_ptr<PropertyDef> &def):
            def(def), value(def->getDefault())
        { }

        void setValue(AutomationValue value);
        [[nodiscard]] AutomationValue getValue() const;
    };
}