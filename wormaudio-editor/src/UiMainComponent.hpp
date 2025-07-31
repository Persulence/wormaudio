// Copyright (c)  2025 Thomas Paley-Menzies
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

#include <juce_gui_basics/juce_gui_basics.h>

#include "editor/Editor.fwd.hpp"

#include "canvas/CentrePanel.hpp"
#include "transport/TransportPanel.hpp"
#include "util/modal/FakeModalDialogue.hpp"

namespace ui
{
    class MainSceneComponent;

    class UiMainComponent : public juce::Component, juce::DeletedAtShutdown, public SimpleCommandTarget
    {
        std::unique_ptr<juce::Component> mainScene;
        editor::ProjectRefreshed::Listener onRefreshed;

        juce::MenuBarComponent menuBar;
        std::unique_ptr<juce::MenuBarModel> menuModel;

        struct Private {};

    public:
        explicit UiMainComponent(Private);

        static UiMainComponent& getInstance()
        {
            static std::mutex mutex;
            static UiMainComponent* instance;

            std::lock_guard lock{mutex};
            if (!instance)
            {
                instance = new UiMainComponent(Private{});
            }

            return *instance;
        }

        ~UiMainComponent() override;

        void setFakeModal(const std::shared_ptr<juce::Component> &dialogue_)
        {
            if (dialogue_)
                dialogue = std::make_unique<FakeModalDialogue>(dialogue_);
            else
                dialogue = nullptr;

            updateDialogue();
        }

        void updateDialogue()
        {
            if (dialogue)
                addAndMakeVisible(dialogue.get());
            else
                removeChildComponent(dialogue.get());

            if (dialogue)
            {
                dialogue->enterModalState();
            }
            resized();
        }

        void resized() override;

        void addToast(std::unique_ptr<Component> toast);
        void removeToast(Component* toast);

    private:
        std::unique_ptr<FakeModalDialogue> dialogue;

        std::mutex toastMutex;
        std::list<std::unique_ptr<juce::Component>> toasts;
    };
}
