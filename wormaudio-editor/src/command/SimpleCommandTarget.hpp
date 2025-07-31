// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
