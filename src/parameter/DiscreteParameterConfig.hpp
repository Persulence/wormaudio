#pragma once

#include "signal/Signal.hpp"
#include "ParameterConfigPanel.hpp"
#include "editor/Editor.hpp"

import parameter;

namespace ui
{
    class DiscreteParameterConfig : public ParameterConfig
    {
        parameter::DiscreteParameterDef &def;

    public:
        explicit DiscreteParameterConfig(const parameter::Parameter &parameter_, parameter::DiscreteParameterDef& def_):
            ParameterConfig(parameter_),
            def(def_)
        {
            auto& min = add(std::make_shared<ValueEntry>("Min value", parameter::parseValue, parameter::toString));
            min.setValue(def.min);
            min.listener = [this, &min](auto val)
            {
                def.min = std::round(val);
                min.setValue(def.min);
                onChange.emit();
            };

            auto& max = add(std::make_shared<ValueEntry>("Max value", parameter::parseValue, parameter::toString));
            max.setValue(def.max);
            max.listener = [this, &max](auto val)
            {
                def.max = std::round(val);
                max.setValue(def.max);
                onChange.emit();
            };
        }

        ~DiscreteParameterConfig() override = default;
    };
}
