#pragma once

#include <memory>
#include <vector>

#include "juce_core/system/juce_PlatformDefs.h"

import parameter;

namespace event
{
    class ParameterList
    {
    public:
        virtual ~ParameterList() = default;

        std::vector<parameter::Parameter> parameters;

        ParameterList() = default;
        virtual void insert(const parameter::Parameter& parameter);
        virtual void remove(const parameter::Parameter& parameter);

        JUCE_DECLARE_NON_COPYABLE(ParameterList)
    };
}
