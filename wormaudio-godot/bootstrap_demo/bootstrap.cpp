// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include <iostream>
#include <memory>
#include <thread>

#include "juce_events/juce_events.h"
#include "api/MessageThreadManager.hpp"
#include "runtime/Runtime.hpp"

int main()
{
    wa::MessageThreadManager manager;

    manager.initContext();

    manager.deInitContext();
}

int goodMain()
{
    std::cout << "This is a test. This is only a test\n";

    // std::unique_ptr<wa::MessageThreadManager> messageThreadManager;
    // messageThreadManager = std::make_unique<wa::MessageThreadManager>();

    // runtime::Runtime r;
    std::unique_ptr<juce::ScopedJuceInitialiser_GUI> scope;
    std::unique_ptr<runtime::Runtime> runtime;

    scope = std::make_unique<juce::ScopedJuceInitialiser_GUI>();

    auto messageThread = std::thread{[&]
    {
        juce::Logger::writeToLog("WormAudio: Initialising message thread");
        juce::MessageManager::getInstance()->setCurrentThreadAsMessageThread();
        juce::MessageManager::getInstance()->runDispatchLoop();
    }};

    juce::MessageManager::callAsync([&]
    {
        std::cout << "Async from message thread\n";
        runtime = std::make_unique<runtime::Runtime>();
        runtime->connectToDevice();
    });

    juce::MessageManager::callAsync([&]
    {
        std::cout << "Stopping message thread\n";
        runtime = nullptr;
        juce::MessageManager::getInstance()->stopDispatchLoop();
    });

    messageThread.join();
}
