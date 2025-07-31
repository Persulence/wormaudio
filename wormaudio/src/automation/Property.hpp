// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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