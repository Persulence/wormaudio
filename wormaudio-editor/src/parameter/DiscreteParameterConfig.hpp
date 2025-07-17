// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "signal/Signal.hpp"
#include "ParameterConfigPanel.hpp"
#include "editor/Editor.hpp"

namespace ui
{
    class DiscreteParameterConfig : public BaseParameterDefFiller<parameter::DiscreteParameterDef>
    {
    public:
        explicit DiscreteParameterConfig(parameter::DiscreteParameterDef& def_):
            BaseParameterDefFiller(def_)
        {
        }

        void initProperties() override
        {
            BaseParameterDefFiller::initProperties();

            auto& min = add(std::make_shared<ValueEntry>("Min value", parameter::parseValue, parameter::toString));
            min.setValue(def.min.getValue());
            min.listener = [this, &min](auto val)
            {
                def.min = std::round(val);
                min.setValue(def.min.getValue());
                onChanged();
            };

            auto& max = add(std::make_shared<ValueEntry>("Max value", parameter::parseValue, parameter::toString));
            max.setValue(def.max.getValue());
            max.listener = [this, &max](auto val)
            {
                def.max = std::round(val);
                max.setValue(def.max.getValue());
                onChanged();
            };
        }
    };
}
