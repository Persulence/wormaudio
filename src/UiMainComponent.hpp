#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <panel/BorderPanel.hpp>

#include "panel/Panel.hpp"
#include "browser/element/ElementBrowserPanel.hpp"
#include "browser/FileBrowserPanel.hpp"
#include "browser/outline/OutlinePanel.hpp"
#include "canvas/CentrePanel.hpp"
#include "inspector/RightInspectorPanel.hpp"
#include "transport/TransportPanel.hpp"
#include "util/modal/FakeModalDialogue.hpp"

namespace ui
{
    // Split into file browser and element browser
    class LeftPanel : public Panel
    {
        // FileBrowserPanel fileBrowser;
        // ElementBrowserPanel elementBrowser;

        BorderPanel<FileBrowserPanel> fileBrowserBorder{};
        BorderPanel<ElementBrowserPanel> elementBrowserBorder;
        BorderPanel<OutlinePanel> outline;
        BorderPanel<TransportPanel> transport{};


        juce::StretchableLayoutManager layout;
        juce::StretchableLayoutResizerBar bar1;
        juce::StretchableLayoutResizerBar bar2;

    public:
        LeftPanel();

    protected:
        void paint(juce::Graphics &g) override;
        void resized() override;
    };

    class RightPanel : public Panel
    {
        BorderPanel<RightInspectorPanel> inspector;

    public:
        explicit RightPanel(InspectorSelectionManager& manager):
            inspector(manager)
        {
            addAndMakeVisible(inspector);
        }

        void resized() override
        {
            inspector.setBounds(getLocalBounds());
        }
    };

    // 'Scene' represents an editor mode, such as 'event def' or 'mixer'.
    class MainSceneComponent : public Panel, public juce::DragAndDropContainer, public InspectorSelectionManager
    {
        LeftPanel leftPanel;
        CentrePanel centrePanel;
        RightPanel rightPanel;

        // ResizeHandle leftHandle;
        juce::StretchableLayoutManager layout;
        juce::StretchableLayoutResizerBar bar1;
        juce::StretchableLayoutResizerBar bar2;

    public:
        MainSceneComponent();

        void resized() override;
    };

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
