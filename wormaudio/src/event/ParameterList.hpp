// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
