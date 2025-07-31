// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
