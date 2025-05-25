#pragma once

#include "panel/Panel.hpp"
#include "FileListPanel.hpp"

namespace ui
{
    /// Responsible for scrolling
    class FileBrowserPanel : public Panel
    {
        FileListPanel listPanel;
        // juce::ScrollBar scrollBar;
        juce::Viewport viewport;

    public:
        FileBrowserPanel()
        {
            // addAndMakeVisible(listPanel);
            addAndMakeVisible(viewport);
            viewport.setViewedComponent(&listPanel, false);
        }

        void resized() override
        {
            listPanel.setBounds(getLocalBounds());
            viewport.setBounds(getLocalBounds());
        }
    };
}