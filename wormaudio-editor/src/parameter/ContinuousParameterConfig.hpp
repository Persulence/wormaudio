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

#include "ParameterConfigPanel.hpp"

struct Eraser
{
    struct Storage
    {
    };

    explicit Eraser(auto data)
    {
        using Type = std::decay_t<decltype(data)>;
        // using Type = decltype(data);

        struct S : Storage
        {
            explicit S(Type t_): t(t_)
            {

            }

            Type t;
        };

        // S s = S{data};
        storage = std::make_unique<S>(data);
    }

private:
    std::unique_ptr<Storage> storage;
};

namespace ui
{
    class ContinuousParameterConfig : public BaseParameterDefFiller<parameter::ContinuousParameterDef>
    {
    public:
        JUCE_DECLARE_NON_COPYABLE(ContinuousParameterConfig)
        explicit ContinuousParameterConfig(parameter::ContinuousParameterDef& def_):
            BaseParameterDefFiller(def_)
        {
        }

    protected:
        void initProperties() override
        {
            BaseParameterDefFiller::initProperties();

            auto& min = add(std::make_shared<ValueEntry>("Min value", parameter::parseValue));
            min.toString = parameter::toString;
            min.setValue(*def.min);
            min.listener = [this](auto val)
            {
                def.min = val;
                onChanged();
            };

            auto& max = add(std::make_shared<ValueEntry>("Max value", parameter::parseValue));
            max.toString = parameter::toString;
            max.setValue(*def.max);
            max.listener = [this](auto val)
            {
                def.max = val;
                onChanged();
            };
        }
    };
}
