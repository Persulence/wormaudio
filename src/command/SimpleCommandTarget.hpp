#pragma once
#include <ranges>

#include "Commands.hpp"
#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    class SimpleCommandTarget : public juce::ApplicationCommandTarget
    {
    public:
        ApplicationCommandTarget* getNextCommandTarget() override
        {
            return findFirstTargetParentComponent();
        }

        void getAllCommands(juce::Array<int> &commands) override
        {
            for (const auto &def: commandsDefs | std::views::values)
            {
                commands.add(def.id);
            }
        }

        void getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo &result) override
        {
            commandsDefs.at(commandID).apply(result);
        }

        bool perform(const InvocationInfo &info) override
        {
            commandsDefs.at(info.commandID).perform(info);
            return true;
        }

    protected:
        void addCommand(CommandAction action)
        {
            commandsDefs.emplace(action.id, action);
        }

        void registerCommands()
        {
            Commands::getInstance().registerAllCommandsForTarget(this);
        }

    private:
        std::unordered_map<juce::CommandID, CommandAction> commandsDefs;
    };
}
