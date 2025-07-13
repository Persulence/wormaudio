// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "ParameterConfigPanel.hpp"

namespace ui
{
    class EnumParameterConfig : public BaseParameterDefFiller<parameter::EnumParameterDef>
    {
    public:
        explicit EnumParameterConfig(parameter::EnumParameterDef& def_):
            BaseParameterDefFiller(def_)
        {
        }

    protected:
        void initProperties() override
        {
            BaseParameterDefFiller::initProperties();
        }
    };
}
