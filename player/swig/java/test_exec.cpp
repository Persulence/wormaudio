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

    std::unique_ptr<binding::NRuntime> runtime;
    std::shared_ptr<event::EventInstance> eventInstance;

    juce::MessageManager::callAsync([&scope, &runtime]
    {
        // std::cout << "Allocating runtime\n";
        runtime = std::make_unique<binding::NRuntime>();
        runtime->connectToDevice();

        binding::NSystem system = binding::NSystem::load("test_system/test_system.proj");
        auto def = system.getEventDef("music");
        auto eventInstance = runtime->instantiate(def.value());
        runtime->setState(player::PLAYING);
        eventInstance->setState(player::PLAYING);
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
