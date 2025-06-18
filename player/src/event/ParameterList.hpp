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

        virtual void insert(const parameter::Parameter& parameter) = 0;
        virtual bool remove(const parameter::Parameter &parameter) = 0;
        virtual std::vector<parameter::Parameter>& getParameters() = 0;
    };

    class ParameterListImpl : public ParameterList
    {
    public:
        ParameterListImpl() = default;

        std::vector<parameter::Parameter> parameters;

        void insert(const parameter::Parameter &parameter) override;
        bool remove(const parameter::Parameter &parameter) override;
        std::vector<parameter::Parameter> & getParameters() override;

        JUCE_DECLARE_NON_COPYABLE(ParameterListImpl)

    };
}
