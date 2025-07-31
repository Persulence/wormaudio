// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
