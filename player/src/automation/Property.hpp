#pragma once
#include <memory>

#include "Automation.hpp"
#include "util/class_util.h"
#include "signal/Signal.hpp"

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

        [[nodiscard]] PropertyName getId() const{ return id; }

        [[nodiscard]] AutomationValue getDefault() const{ return defaultValue; }
    };

    class PropertyInstance
    {
    public:
        using OnChanged = signal_event::Callback<AutomationValue>;

        std::shared_ptr<PropertyDef> def;
        OnChanged::Signal onChanged;

        JUCE_DECLARE_NON_COPYABLE(PropertyInstance)

        explicit PropertyInstance(const std::shared_ptr<PropertyDef> &def):
            def(def), value(def->getDefault())
        { }

        void setValue(AutomationValue value);
        [[nodiscard]] AutomationValue getValue() const;

    private:
        AutomationValue value{};
    };
}