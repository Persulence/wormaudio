// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "property/PropertyFiller.hpp"
#include "state/ConditionList.hpp"

namespace ui
{
    /// Base class for condition property fillers. Impl contains std::variant visitor for conditions.
    class ConditionPropertyFiller : public PropertyFiller
    {
    public:
        static std::unique_ptr<PropertyFiller> create(condition::Condition& condition);
    };
}
