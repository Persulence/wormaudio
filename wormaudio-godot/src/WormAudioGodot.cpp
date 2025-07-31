
// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "WormAudioGodot.hpp"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/thread.hpp>
#include <juce_events/juce_events.h>

#include <api/MessageThreadManager.hpp>
#include <runtime/Runtime.hpp>

namespace wa
{
    WormAudioGodot::WormAudioGodot()
    {
        manager = std::make_unique<MessageThreadManager>();
    }

    WormAudioGodot::~WormAudioGodot()
    {
        // if (messageThread.joinable())
        // {
        //     messageThreadManager->requestMessageThreadStop();
        //     messageThread.join();
        // }
    }

    runtime::Runtime& WormAudioGodot::getRuntime() const
    {
        return manager->getRuntime();
    }

    void WormAudioGodot::initContext() const
    {
        manager->initContext();
        callAsync([this]
        {
            manager->getRuntime().connectToDevice();
        });
    }

    void WormAudioGodot::deInitContext() const
    {
        callAsync([this]
        {
            manager->getRuntime().disconnect();
        });
        manager->deInitContext();
    }

    void WormAudioGodot::log(const std::string &message)
    {
        log(INFO, message);
    }

    void WormAudioGodot::log(const Level level, const std::string &message)
    {
        const std::string fullMessage = "[WormAudio] " + message;
        switch (level)
        {
        case INFO:
            godot::UtilityFunctions::print(fullMessage.data());
            break;
        default:
            godot::UtilityFunctions::printerr(fullMessage.data());
            break;
        }
    }

    void WormAudioGodot::callAsync(std::function<void()> f)
    {
        juce::MessageManager::callAsync(f);
    }

    void WormAudioGodot::callSync(std::function<void()> f)
    {
        juce::MessageManager::callSync(f);
    }
}
