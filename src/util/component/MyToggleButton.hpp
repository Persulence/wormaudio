#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "util/Data.hpp"

namespace ui
{
    class MyToggleButton : public juce::ToggleButton
    {
    public:
        void setData(util::Data<bool> data_)
        {
            data.removeListener(&listener);
            data = data_;

            data.setupListener(&listener, [this](auto& t)
            {
                setToggleState(t, juce::dontSendNotification);
            });

            setToggleState(*data, juce::dontSendNotification);
        }

        void buttonStateChanged() override
        {
            data = getToggleStateValue().getValue();
        }

    private:
        util::Data<bool>::Listener listener;
        util::Data<bool> data{false};
    };
}
