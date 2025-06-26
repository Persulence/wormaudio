#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "canvas/CentrePanel.hpp"
#include "scene/MainSceneComponent.hpp"
#include "transport/TransportPanel.hpp"
#include "util/modal/FakeModalDialogue.hpp"

namespace ui
{
    class UiMainComponent : public juce::Component, juce::DeletedAtShutdown, public SimpleCommandTarget
    {
        juce::MenuBarComponent menuBar;
        MainSceneComponent mainScene;
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

    private:
        std::unique_ptr<FakeModalDialogue> dialogue;

        std::unique_ptr<juce::FileChooser> fileChooser;
    };
}
