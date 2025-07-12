#include <iostream>

#include "../runtime.b.hpp"


int main()
{
    std::cout << "This is a test. This is only a test\n";

    binding::MessageThreadManager scope;

    std::unique_ptr<binding::NRuntime> runtime;

    juce::MessageManager::callAsync([&scope, &runtime]
    {
        std::cout << "Allocating runtime\n";
        runtime = std::make_unique<binding::NRuntime>();
    });
    juce::MessageManager::callAsync([&scope, &runtime]
    {
        std::cout << "Destroying runtime\n";
        runtime = nullptr;
    });
    juce::MessageManager::callAsync([&scope]
    {
        std::cout << "Requesting stop\n";
        scope.requestMessageThreadStop();
    });

    // scope.join();
}
