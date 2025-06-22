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
                label.setText(t, juce::dontSendNotification);
            });

            label.setText(*data, juce::dontSendNotification);
        }

        void labelTextChanged(Label *labelThatHasChanged) override
        {
            data.setValue(labelThatHasChanged->getText().toStdString());
        }

    private:
        Label label;
        typename util::Data<T>::Listener listener;
        util::Data<T> data{""};
    };
}
