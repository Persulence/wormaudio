// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>

#include "runtime/Runtime.hpp"

namespace wa
{
    class MessageThreadManager
    {
    public:
        // using OnClose = signal_event::Callback<>;

        MessageThreadManager()
        {
        }

        ~MessageThreadManager()
        {
        }

        void initContext()
        {
            scope = std::make_unique<juce::ScopedJuceInitialiser_GUI>();

            messageThread = std::make_unique<std::thread>([&]
            {
                juce::Logger::writeToLog("WormAudio: Initialising message thread");
                juce::MessageManager::getInstance()->setCurrentThreadAsMessageThread();
                juce::MessageManager::getInstance()->runDispatchLoop();
            });

            juce::MessageManager::callAsync([&]
            {
                juce::Logger::writeToLog("WormAudio: Initialising runtime from message thread");
                runtime = std::make_unique<runtime::Runtime>();
                runtime->connectToDevice();
            });
        }

        void deInitContext()
        {
            if (messageThread)
            {
                juce::MessageManager::callAsync([&]
                {
                    juce::Logger::writeToLog("WormAudio: Stopping message thread");
                    runtime = nullptr;
                    juce::MessageManager::getInstance()->stopDispatchLoop();

                });

                if (messageThread->joinable())
                    messageThread->join();

                scope = nullptr;
            }
        }

        runtime::Runtime & getRuntime() const
        {
            assert(runtime);

            return *runtime;
        }

        // static void claimMessageThread()
        // {
        //     juce::Logger::writeToLog("WormAudio: Initialising message thread");
        //     juce::MessageManager::getInstance()->setCurrentThreadAsMessageThread();
        //     juce::MessageManager::getInstance()->runDispatchLoop();
        // }
        //
        // void requestMessageThreadStop()
        // {
        //     juce::MessageManager::callAsync([this]
        //     {
        //         onClose.emit();
        //         juce::MessageManager::getInstance()->stopDispatchLoop();
        //     });
        // }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MessageThreadManager)

        std::unique_ptr<juce::ScopedJuceInitialiser_GUI> scope{};
        std::unique_ptr<std::thread> messageThread;
        std::unique_ptr<runtime::Runtime> runtime;
    };
}
