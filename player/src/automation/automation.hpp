#pragma once
#include <memory>

using AutomationValue = float;

namespace automation
{
    using PropertyIdentifier = std::string;

    class PropertyDef;
    using Property = std::shared_ptr<PropertyDef>;

    class PropertyInstance;
    class PropertyInstanceHandle
    {
        std::shared_ptr<PropertyInstance> instance;

    public:
        explicit PropertyInstanceHandle(std::shared_ptr<PropertyInstance> instance_):
            instance(instance_)
        {

        }

        // void setValue(AutomationValue value);
        // AutomationValue getValue();

        PropertyInstance* operator->() const
        {
            return instance.get();
        }
    };
}