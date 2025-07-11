#pragma once

#include "bindings.h"
#include "juce_gui_basics/juce_gui_basics.h"
#include "runtime/Runtime.hpp"

namespace binding
{
    class RuntimeManager : WrapperBase, public juce::JUCEApplication
    {
    public:
        RuntimeManager()
        {
            juce::Logger::getCurrentLogger()->writeToLog("Initialising JUCE");
        }

        const juce::String getApplicationName() override
        {
            return "NEEPSound";
        }

        const juce::String getApplicationVersion() override { return "bindings"; }

        void initialise(const juce::String &commandLineParameters) override
        {
        }

        void shutdown() override
        {

        }
    };

    class NRuntime : WrapperBase
    {
    public:
        NRuntime();
        std::shared_ptr<event::EventInstance> instantiate(const binding::NEventDef &def) const;
        void startMessageManager() const;
        void stopMessageManager() const;
        void connectToDevice() const;
        void disconnect() const;

    private:
        std::unique_ptr<runtime::Runtime> backing;
    };
}
