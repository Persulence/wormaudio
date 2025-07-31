// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
