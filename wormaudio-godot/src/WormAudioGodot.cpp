
// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
