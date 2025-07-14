// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>

#include "signal/Signal.hpp"

namespace wa
{
    class MessageThreadManager
    {
    public:
        using OnClose = signal_event::Callback<void>;

        OnClose::Signal onClose;

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

        void requestMessageThreadStop()
        {
            juce::MessageManager::callAsync([this]
            {
                onClose.emit();
                juce::MessageManager::getInstance()->stopDispatchLoop();
            });
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MessageThreadManager)

        juce::ScopedJuceInitialiser_GUI scope{};
    };
}
