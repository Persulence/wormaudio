// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "browser/FileBrowserPanel.hpp"
#include "browser/element/ElementBrowserPanel.hpp"
#include "browser/outline/OutlinePanel.hpp"
#include "canvas/CentrePanel.hpp"
#include "inspector/RightInspectorPanel.hpp"
#include "panel/BorderPanel.hpp"
#include "panel/Panel.hpp"
#include "state/condition/AllElementsDoneCondition.hpp"
#include "transport/TransportPanel.hpp"
#include "widget/SpatialSelectorWidget.hpp"
#include "editor/Editor.fwd.hpp"

namespace ui
{
    // Split into file browser and element browser
    class LeftPanel : public Panel
    {
        // FileBrowserPanel fileBrowser;
        // ElementBrowserPanel elementBrowser;

        BorderPanel<FileBrowserPanel> fileBrowserBorder{};
        // BorderPanel<ElementBrowserPanel> elementBrowserBorder;
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
    public:
        explicit RightPanel(InspectorSelectionManager& manager);

        void resized() override;

    private:
        BorderPanel<RightInspectorPanel> inspector;
        BorderPanel<SpatialPreviewPanel> spatial;
        juce::StretchableLayoutManager layout;
        juce::StretchableLayoutResizerBar bar;
    };

    // 'Scene' represents an editor mode, such as 'event def' or 'mixer'.
    class MainSceneComponent : public Panel, public juce::DragAndDropContainer, public InspectorSelectionManager, public SimpleCommandTarget
    {
        LeftPanel leftPanel;
        CentrePanel centrePanel;
        RightPanel rightPanel;

        // ResizeHandle leftHandle;
        juce::StretchableLayoutManager layout;
        juce::StretchableLayoutResizerBar bar1;
        juce::StretchableLayoutResizerBar bar2;
        editor::EventChanged::Listener eventChangedListener;

    public:
        MainSceneComponent();

        void resized() override;
    };
}
