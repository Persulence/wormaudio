// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
