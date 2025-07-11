#include <iostream>

#include "../runtime.b.hpp"

class JuceScopeManager
{

};

int main()
{
    std::cout << "This is a test. This is only a test\n";

    // binding::RuntimeManager rm;
    // rm.main();

    juce::ScopedJuceInitialiser_GUI scope;

    // auto t = std::thread{[]
    // {
        // juce::MessageManager::getInstance()->stopDispatchLoop();
    // }};

    juce::MessageManager::callAsync([]
    {
        binding::NRuntime runtime;
        juce::MessageManager::getInstance()->stopDispatchLoop();
    });

    juce::MessageManager::getInstance()->setCurrentThreadAsMessageThread();
    juce::MessageManager::getInstance()->runDispatchLoop();

    // t.join();
}
