#pragma once

#include "ParameterConfigPanel.hpp"

namespace ui
{
    class EnumParameterConfig : public BaseParameterDefProperties<parameter::EnumParameterDef>
    {
    public:
        explicit EnumParameterConfig(parameter::EnumParameterDef& def_):
            BaseParameterDefProperties(def_)
        {
        }

    protected:
        void initProperties() override
        {

        }
    };
}
