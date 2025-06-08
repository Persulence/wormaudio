
#include "Property.hpp"

namespace automation
{
    void PropertyInstance::setValue(const AutomationValue value_)
    {
        value = value_;
        onChanged.emit(value);
    }

    AutomationValue PropertyInstance::getValue() const
    {
        return value;
    }

    // void PropertyHandle::setValue(AutomationValue value)
    // {
    //
    // }
    //
    // AutomationValue PropertyHandle::getValue()
    // {
    //
    // }
}
