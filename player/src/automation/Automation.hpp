// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <memory>
#include <utility>

using AutomationValue = float;

namespace automation
{
    using PropertyName = std::string;

    class PropertyDef;
    using Property = std::shared_ptr<PropertyDef>;

    class PropertyInstance;
    class PropertyInstanceHandle
    {
        // May change to raw or weak
        std::shared_ptr<PropertyInstance> instance;

    public:
        explicit PropertyInstanceHandle(std::shared_ptr<PropertyInstance> instance_):
            instance(std::move(instance_))
        {

        }

        PropertyInstance* operator->() const
        {
            return instance.get();
        }
    };

    enum class Unit
    {
        NONE,
        DBFS,
        HZ,
    };

    // EXTERNAL_SERIALIZE(Unit)
    // {
    //
    // }

    Property createProperty(PropertyName id, AutomationValue defaultVal, Unit unit);

}
