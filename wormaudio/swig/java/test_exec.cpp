// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include <iostream>

#include "../runtime.b.hpp"


int main()
{
    std::cout << "This is a test. This is only a test\n";

    binding::MessageThreadManager scope;
    auto messageThread = std::thread{[]
    {
        binding::MessageThreadManager::claimMessageThread();
    }};

    std::unique_ptr<binding::WARuntime> runtime;
    std::shared_ptr<event::EventInstance> eventInstance;

    juce::MessageManager::callAsync([&scope, &runtime]
    {
        // std::cout << "Allocating runtime\n";
        runtime = std::make_unique<binding::WARuntime>();
        runtime->connectToDevice();

        binding::WASystem system = binding::WASystem::load("test_system/test_system.proj");
        auto def = system.getEventDef("music");
        auto eventInstance = runtime->instantiate(def.value());
        runtime->setState(player::PLAYING);
        eventInstance->transport.setState(player::PLAYING);
        eventInstance->setPosition({0, 0, 0});
    });
    juce::MessageManager::callAsync([&scope, &runtime]
    {

        // std::cout << "Destroying runtime\n";
        // runtime->disconnect();
        // runtime = nullptr;
    });
    juce::MessageManager::callAsync([&scope]
    {
        // std::cout << "Requesting stop\n";
        // scope.requestMessageThreadStop();
    });

    messageThread.join();
}
