// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
