#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <panel/BorderPanel.hpp>

#include "panel/Panel.hpp"
#include "browser/ElementBrowserPanel.hpp"
#include "browser/FileBrowserPanel.hpp"
#include "canvas/StateCanvasPanel.hpp"
#include "panel/ResizeHandle.hpp"
#include "canvas/CentrePanel.hpp"
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

        juce::StretchableLayoutManager layout;
        juce::StretchableLayoutResizerBar bar1;
        juce::StretchableLayoutResizerBar bar2;

    public:
        LeftPanel();

    protected:
        void paint(juce::Graphics &g) override;
        void resized() override;
    };

    class UiMainComponent : public Panel, public juce::DragAndDropContainer
    {
        LeftPanel leftPanel;
        CentrePanel centrePanel;

        // ResizeHandle leftHandle;
        juce::StretchableLayoutManager layout;
        juce::StretchableLayoutResizerBar bar;

    public:

        UiMainComponent();

        void resized() override;
    };

    // void setupLookAndFeel(juce::Component& component);
}
