#pragma once

#include <juce_events/juce_events.h>

import event;

namespace runtime
{
    class LogicTicker : juce::Timer
    {
        int intervalMs{100};

    public:
        std::function<void()> callback{[]{}};

        explicit LogicTicker()
        {

        }

        // TODO:
        // void setInterval(int interval)
        // {
        //
        // }

        void start()
        {
            startTimer(intervalMs);
        }

        void stop()
        {
            stopTimer();
        }

    protected:
        void timerCallback() override
        {
            callback();
        }
    };
}
