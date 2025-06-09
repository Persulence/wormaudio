#pragma once

#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    class Commands : public juce::ApplicationCommandManager, public juce::DeletedAtShutdown
    {
    public:
        static constexpr juce::CommandID QUIT = juce::StandardApplicationCommandIDs::quit;
        static constexpr juce::CommandID DEL = juce::StandardApplicationCommandIDs::del;

        static Commands& getInstance()
        {
            static std::mutex mutex;
            // static std::unique_ptr<CommandManager> instance;
            static Commands* instance;

            std::lock_guard lock{mutex};
            if (!instance)
            {
                // instance = std::make_unique<CommandManager>();
                // Deleted by DeletedAtShutdown
                instance = new Commands{};
            }
            return *instance;
        }

    private:
        Commands()
        {
        }
    };

    // class Commands : public juce::DeletedAtShutdown
    // {
    // public:

        // juce::ApplicationCommandInfo quit{QUIT};
        //
        // juce::ApplicationCommandInfo del{DEL};
        // juce::ApplicationCommandInfo copy{juce::StandardApplicationCommandIDs::copy};
        // juce::ApplicationCommandInfo cut{juce::StandardApplicationCommandIDs::cut};
        // juce::ApplicationCommandInfo paste{juce::StandardApplicationCommandIDs::paste};
        //
        // juce::ApplicationCommandInfo undo{juce::StandardApplicationCommandIDs::undo};
        // juce::ApplicationCommandInfo redo{juce::StandardApplicationCommandIDs::redo};
    // };

}