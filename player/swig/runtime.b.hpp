// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "bindings.h"
#include "runtime/Runtime.hpp"

namespace binding
{
    class MessageThreadManager : WrapperBase
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
            juce::Logger::writeToLog("NEEPSound: Initialising message thread");
            juce::MessageManager::getInstance()->setCurrentThreadAsMessageThread();
            juce::MessageManager::getInstance()->runDispatchLoop();
        }

        static void requestMessageThreadStop()
        {
            juce::MessageManager::getInstance()->stopDispatchLoop();
        }

    private:
        DISABLE_COPY(MessageThreadManager);
        DISABLE_MOVE(MessageThreadManager);

        juce::ScopedJuceInitialiser_GUI scope{};

        // std::thread messageThread = std::thread{[]
        // {
        //     juce::MessageManager::getInstance()->setCurrentThreadAsMessageThread();
        //     juce::MessageManager::getInstance()->runDispatchLoop();
        // }};
    };

    class NRuntime : WrapperBase
    {
    public:
        NRuntime();
        ~NRuntime() = default;

        std::shared_ptr<event::EventInstance> instantiate(const binding::NEventDef &def) const;
        void connectToDevice() const;
        void disconnect() const;

        void setState(player::TransportState state) const;

    private:
        std::unique_ptr<runtime::Runtime> backing;
    };
}
