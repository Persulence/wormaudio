
// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
