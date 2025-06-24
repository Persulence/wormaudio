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
