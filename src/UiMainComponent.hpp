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

namespace ui
{
    // Split into file browser and element browser
    class LeftPanel : public Panel
    {
        // FileBrowserPanel fileBrowser;
        // ElementBrowserPanel elementBrowser;

        BorderPanel<FileBrowserPanel> fileBrowserBorder{};
        BorderPanel<ElementBrowserPanel> elementBrowserBorder{};
        BorderPanel<TransportPanel> transport{};

        BorderPanel<OutlinePanel> outline;

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

    class UiMainComponent : public juce::Component
    {
        juce::Toolbar toolbar;
        MainSceneComponent mainScene;

    public:
        UiMainComponent();
        ~UiMainComponent() override;

        void resized() override;
    };
}
