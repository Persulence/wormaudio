#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "ParameterConfigPanel.hpp"

import parameter;

struct Eraser
{
    struct Storage
    {
    };

    Eraser(auto data)
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
    class ContinuousParameterConfig : public BaseParameterDefProperties<parameter::ContinuousParameterDef>
    {
    public:
        JUCE_DECLARE_NON_COPYABLE(ContinuousParameterConfig)
        explicit ContinuousParameterConfig(parameter::ContinuousParameterDef& def_):
            BaseParameterDefProperties(def_)
        {
            ContinuousParameterConfig::initProperties();
        }

    protected:
        void initProperties() override
        {
            auto& min = add(std::make_shared<ValueEntry>("Min value", parameter::parseValue));
            min.toString = parameter::toString;
            min.setValue(def.min);
            min.listener = [this](auto val)
            {
                def.min = val;
                onChanged();
            };

            auto& max = add(std::make_shared<ValueEntry>("Max value", parameter::parseValue));
            max.toString = parameter::toString;
            max.setValue(def.max);
            max.listener = [this](auto val)
            {
                def.max = val;
                onChanged();
            };
        }
    };
}
