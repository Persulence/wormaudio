#pragma once

#include <memory>
#include <vector>

#include "juce_core/system/juce_PlatformDefs.h"
#include "resource/SharedResource.hpp"

import parameter;

namespace event
{
    class ParameterList : public resource::SharedResource
    {
    public:
        ~ParameterList() override = default;

        std::vector<parameter::Parameter> parameters;

        ParameterList() = default;
        virtual void insert(const parameter::Parameter& parameter);
        virtual bool remove(const parameter::Parameter &parameter);

        JUCE_DECLARE_NON_COPYABLE(ParameterList)
    };
}
