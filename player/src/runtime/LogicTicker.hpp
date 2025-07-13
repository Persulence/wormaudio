// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <juce_events/juce_events.h>

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
