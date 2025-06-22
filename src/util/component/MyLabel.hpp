#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "util/Data.hpp"

namespace ui
{
    template <typename T>
    class MyLabel : public juce::Label, juce::Label::Listener
    {
    public:
        void setData(util::Data<T> data_)
        {
            data.removeListener(&listener);
            data = data_;

            data.setupListener(&listener, [this](auto& t)
            {
                setText(t, juce::dontSendNotification);
            });

            setText(*data, juce::dontSendNotification);
            addListener(this);
        }

        void labelTextChanged(Label *labelThatHasChanged) override
        {
            data.setValue(labelThatHasChanged->getText().toStdString());
        }

    private:
        typename util::Data<T>::Listener listener;
        util::Data<T> data{""};
    };
}
