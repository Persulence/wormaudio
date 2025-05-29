#pragma once

#include "panel/Panel.hpp"
#include "FileListPanel.hpp"

namespace ui
{
    /// Responsible for scrolling
    class FileBrowserPanel : public Panel, juce::ScrollBar::Listener
    {
        FileListPanel listPanel;
        juce::ScrollBar scrollBar;
        // juce::Viewport viewport;

    public:
        FileBrowserPanel():
            scrollBar(true)
        {
            addAndMakeVisible(listPanel);
            listPanel.callback = [this](int items)
            {
                if (getHeight() > 0)
                {
                    auto expected = listPanel.getExpectedHeight();
                    scrollBar.setRangeLimits(0,
                        listPanel.getExpectedHeight() / getHeight(),
                        // listPanel.getExpectedHeight(),
                        // getHeight(),
                        juce::dontSendNotification);
                }
            };

            addAndMakeVisible(scrollBar);
            scrollBar.setAutoHide(false); // TODO: fix
            // scrollBar.setRangeLimits(juce::Range(0.0, 2.0), juce::dontSendNotification);
            scrollBar.addListener(this);
        }

        void resized() override
        {
            // I have no idea how to make the scrollbar thumb adopt the correct size
            scrollBar.setBounds(getLocalBounds().removeFromRight(10));
            listPanel.setBounds(getLocalBounds().withHeight(listPanel.getExpectedHeight()));
            listPanel.updateVisibilities();
            if (getHeight() > 0) // Avoid / 0
                scrollBar.setRangeLimits(0, listPanel.getHeight() / getHeight());
            scrollBar.toFront(false);
        }

        void scrollBarMoved(juce::ScrollBar *scrollBarThatHasMoved, double newRangeStart) override
        {
            listPanel.setScroll(newRangeStart / scrollBarThatHasMoved->getMaximumRangeLimit());
        }

        void mouseWheelMove(const juce::MouseEvent &event, const juce::MouseWheelDetails &wheel) override
        {
            // Use events for scrolling
            scrollBar.mouseWheelMove(event, wheel);
        }
    };
}