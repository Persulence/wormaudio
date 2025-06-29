#pragma once
#include "transition/condition/ConditionPropertyFiller.hpp"

namespace ui
{
    class TimeConditionFiller : public ConditionPropertyFiller
    {
    public:
        explicit TimeConditionFiller(condition::TimeCondition& condition_);

        void initProperties() override;

    private:
        DISABLE_COPY(TimeConditionFiller)
        DISABLE_MOVE(TimeConditionFiller)

        condition::TimeCondition &condition;
        util::Data<bool>::Listener useTempoListener;
        util::Data<double> timeBeats;
        util::Data<double>::MultiListener timeBeatsListener;
        util::Data<player::TimeSignature>::MultiListener timeSigListener;
    };
}
