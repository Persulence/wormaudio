// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>

namespace wa
{
    class MessageThreadManager
    {
    public:
        MessageThreadManager()
        {
        }

        ~MessageThreadManager()
        {
        }

        static void claimMessageThread()
        {
            juce::Logger::writeToLog("WormAudio: Initialising message thread");
            juce::MessageManager::getInstance()->setCurrentThreadAsMessageThread();
            juce::MessageManager::getInstance()->runDispatchLoop();
        }

        static void requestMessageThreadStop()
        {
            juce::MessageManager::getInstance()->stopDispatchLoop();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MessageThreadManager)

        juce::ScopedJuceInitialiser_GUI scope{};
    };
}
