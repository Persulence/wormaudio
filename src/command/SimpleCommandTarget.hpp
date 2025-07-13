// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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

        void getCommandInfo(const juce::CommandID commandID, juce::ApplicationCommandInfo &result) override
        {
            commandsDefs.at(commandID).apply(result);
        }

        bool perform(const InvocationInfo &info) override
        {
            commandsDefs.at(info.commandID).perform(info);
            return true;
        }

    protected:
        class Builder
        {
            SimpleCommandTarget& parent;

        public:
            explicit Builder(SimpleCommandTarget& parent_): parent(parent_) {}

            Builder& add(CommandAction action)
            {
                parent.commandsDefs.emplace(action.id, action);
                return *this;
            }

            void finish() const
            {
                Commands::getInstance().registerAllCommandsForTarget(&parent);
            }
        };

        Builder commands()
        {
            return Builder{*this};
        }

    private:
        std::unordered_map<juce::CommandID, CommandAction> commandsDefs;
    };
}
