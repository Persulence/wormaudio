#pragma once
#include <memory>

#include "automation.hpp"

using AutomationValue = float;

namespace automation
{
    class PropertyDef
    {
        AutomationValue defaultValue{};
        PropertyIdentifier id;
        // TODO: log scale and unit

    public:
        explicit PropertyDef(const AutomationValue defaultValue_):
            defaultValue(defaultValue_)
        {

        }
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