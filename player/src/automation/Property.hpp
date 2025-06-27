#pragma once
#include <memory>

#include "cereal/cereal.hpp"

#include "Automation.hpp"
#include "signal/Signal.hpp"
#include "util/serialization_util.hpp"

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

    private:
        FRIEND_CEREAL

        INTERNAL_SERIALIZE
        {
            ar(cereal::make_nvp("id", id),
                cereal::make_nvp("default_value", defaultValue),
                cereal::make_nvp("unit", unit)
                );
        }

        LOAD_AND_CONSTRUCT(PropertyDef)
        {
            PropertyName id;
            AutomationValue defaultValue;
            Unit unit;

            ar(cereal::make_nvp("id", id),
                cereal::make_nvp("default_value", defaultValue),
                cereal::make_nvp("unit", unit)
                );

            construct(id, defaultValue, unit);
        }
    };

    class PropertyInstance
    {
    public:
        using OnChanged = signal_event::Callback<AutomationValue>;

        std::shared_ptr<PropertyDef> def;
        OnChanged::Signal onChanged;

        DISABLE_COPY(PropertyInstance)

        explicit PropertyInstance(const std::shared_ptr<PropertyDef> &def):
            def(def), value(def->getDefault())
        { }

        void setValue(AutomationValue value);
        [[nodiscard]] AutomationValue getValue() const;

    private:
        AutomationValue value{};
    };
}