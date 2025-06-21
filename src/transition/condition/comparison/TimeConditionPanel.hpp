#pragma once
#include "transition/condition/ConditionPanel.hpp"

namespace ui
{
    class TimeConditionPanel : public ConditionPanel
    {
    public:
        explicit TimeConditionPanel(condition::TimeCondition& condition_);

        void initProperties() override;

    private:
        condition::TimeCondition &condition;
    };
}
