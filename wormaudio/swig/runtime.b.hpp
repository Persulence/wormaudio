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
            juce::Logger::writeToLog("WormAudio: Initialising message thread");
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
    };

    class WARuntime : WrapperBase
    {
    public:
        WARuntime();
        ~WARuntime() = default;

        std::shared_ptr<event::EventInstance> instantiate(const binding::WASoundDef &def) const;
        void connectToDevice() const;
        void disconnect() const;
        void setListenerPosition(double x, double y, double z) const;
        void setListenerYaw(float yaw) const;

        void clearInstances() const;

        int getInstanceCount() const;

        void setState(player::TransportState state) const;

    private:
        std::unique_ptr<runtime::Runtime> backing;
    };
}
