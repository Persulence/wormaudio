// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "property/PropertyFiller.hpp"
#include "state/condition/RandomCondition.hpp"

namespace ui
{
    class RandomConditionFiller : public PropertyFiller
    {
    public:
        explicit RandomConditionFiller(condition::RandomCondition& condition_);

        void initProperties() override;

    private:
        condition::RandomCondition& condition;
    };
}
