// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include "GlobalParameterLookup.hpp"

namespace sm
{
    /**
     * When event-local parameters are added, this will append them to the available list.
     * For now, it wraps global parameters with the state timer.
     */
    class EventParameterLookup : public parameter::ParameterLookup
    {
    public:
        EventParameterLookup() = default;

        // Slightly dubious
        void setParent(GlobalParameterLookup* globalParameterLookup_)
        {
            globalParameters = globalParameterLookup_;
        }

        void resetStateTimer(player::Sample sample);
        player::Sample getReference(player::TimeType type) const;

        ParameterValue getValue(const std::string& name) const override { return globalParameters->getValue(name); }
        parameter::ParameterInstance& get(const parameter::Parameter& parameter) const override{ return globalParameters->get(parameter); }
        parameter::ParameterInstance& get(const std::string& name) const override { return globalParameters->get(name); }

    private:
        GlobalParameterLookup* globalParameters;

        player::Sample lastStateEnter{0};
    };

}