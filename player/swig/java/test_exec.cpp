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

    juce::MessageManager::callAsync([&scope, &runtime]
    {
        // std::cout << "Allocating runtime\n";
        runtime = std::make_unique<binding::NRuntime>();
        runtime->connectToDevice();
    });
    juce::MessageManager::callAsync([&scope, &runtime]
    {
        // std::cout << "Destroying runtime\n";
        runtime->disconnect();
        runtime = nullptr;
    });
    juce::MessageManager::callAsync([&scope]
    {
        // std::cout << "Requesting stop\n";
        scope.requestMessageThreadStop();
    });

    messageThread.join();
}
