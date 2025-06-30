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