// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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

    private:
        typename util::Data<T>::Listener listener;
        util::Data<T> data{{}};
    };
}
