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
