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
#include "util/parse.hpp"

namespace ui
{
    template <typename T>
    class MyLabel : public juce::Label, juce::Label::Listener
    {
    public:
        using Parse = std::function<T(std::string)>;
        using ToString = std::function<std::string(T)>;

        Parse parse;
        ToString toString;

        explicit MyLabel(Parse parse_ = [](const std::string& str){ return str; }, ToString toString_ = ui::parse::defaultToString<T>):
            parse(parse_), toString(std::move(toString_))
        {

        }

        void listen(typename signal_event::Callback<T>::Signal* signal)
        {
            signal->setup(&extraListener, [this](auto val)
            {
                setText(toString(val), juce::dontSendNotification);
            });
        }

        void setData(util::Data<T> data_)
        {
            listener.unListen();
            // data.removeListener(&listener);
            data = data_;

            data.setupListener(&listener, [this](auto& t)
            {
                setText(toString(t), juce::dontSendNotification);
            });

            setText(toString(*data), juce::dontSendNotification);
            addListener(this);
        }

        void labelTextChanged(Label *labelThatHasChanged) override
        {
            data.setValue(parse(labelThatHasChanged->getText().toStdString()));
        }

        void setTextParse(T value)
        {
            setText(toString(value), juce::dontSendNotification);
        }

    private:
        typename util::Data<T>::Listener listener;
        typename signal_event::Callback<T>::Listener extraListener;
        util::Data<T> data{{}};
    };
}
