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
        FileBrowserPanel():
            listPanel(FileListPanel{viewport})
        {
            // addAndMakeVisible(listPanel);
            addAndMakeVisible(viewport);
            viewport.setViewedComponent(&listPanel, false);
        }

        void resized() override
        {
            viewport.setBounds(getLocalBounds());
            listPanel.setBounds(getLocalBounds().withHeight(listPanel.getExpectedHeight()));
        }
    };
}