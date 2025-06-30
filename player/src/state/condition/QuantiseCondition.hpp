#pragma once

#include "Condition.hpp"
#include "util/Data.hpp"
#include "util/serialization_util.hpp"

namespace condition
{
    class QuantiseCondition : public ConditionBase<QuantiseCondition>
    {
    public:
        util::Data<bool> useTempo{true};
        player::Tempo tempo;
        util::Data<player::Seconds> intervalSeconds{1};
        util::Data<double> intervalBeats{4};

        QuantiseCondition();

        [[nodiscard]] player::Sample testImpl(const sm::EventParameterLookup &pl, const event::LogicTickInfo &info, const sm::StateInstance &currentState) const;

    private:

        FRIEND_CEREAL
        INTERNAL_SERIALIZE
        {
            using namespace cereal;
            ar(make_nvp("useTempo", useTempo));
            ar(make_nvp("tempo", tempo));
            ar(make_nvp("intervalSeconds", intervalSeconds));
            ar(make_nvp("intervalBeats", intervalBeats));
        }
    };
}
