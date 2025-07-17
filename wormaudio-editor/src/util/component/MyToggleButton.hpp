// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "util/Data.hpp"

namespace ui
{
    class MyToggleButton : public juce::ToggleButton, public juce::Value::Listener
    {
    public:
        void setData(util::Data<bool> data_)
        {
            // data.removeListener(&listener);
            listener.unListen();
            data = data_;

            data.setupListener(&listener, [this](auto& t)
            {
                setToggleState(t, juce::dontSendNotification);
            });

            setToggleState(*data, juce::dontSendNotification);
            getToggleStateValue().addListener(this);
        }

        void buttonStateChanged() override
        {
            // auto state = getState();
            // if (state != buttonOver && (state == buttonDown) != *data)
            // {
            // }
        }

        void valueChanged(juce::Value &value) override
        {
            bool toggle = getToggleState();
            if (toggle != *data)
                data = toggle;
        }

    private:
        util::Data<bool>::Listener listener;
        util::Data<bool> data{false};
    };
}
