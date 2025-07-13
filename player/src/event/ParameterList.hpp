// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <memory>
#include <vector>

#include "cereal/types/vector.hpp"

#include "util/class_util.h"
#include "resource/SharedResource.hpp"
#include "state/Parameter.hpp"
#include "util/serialization_util.hpp"

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
        std::vector<resource::ResourceHandle> getChildResources() override;

        JUCE_DECLARE_NON_COPYABLE(ParameterListImpl)

    private:
        FRIEND_CEREAL

        INTERNAL_SERIALIZE
        {
            ar(parameters);
        }
    };
}
