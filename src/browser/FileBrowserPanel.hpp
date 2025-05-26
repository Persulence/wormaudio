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
            // addAndMakeVisible(listPanel);
            // addAndMakeVisible(viewport);
            // viewport.setViewedComponent(&listPanel, false);

            addAndMakeVisible(listPanel);
            listPanel.callback = [this](int items)
            {
                if (getHeight() > 0)
                {
                    scrollBar.setRangeLimits(0,
                        listPanel.getExpectedHeight() / getHeight(),
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
            // viewport.setBounds(getLocalBounds());
            scrollBar.setBounds(getLocalBounds().removeFromRight(10));
            listPanel.setBounds(getLocalBounds().withHeight(listPanel.getExpectedHeight()));
            scrollBar.toFront(false);
        }

        void scrollBarMoved(juce::ScrollBar *scrollBarThatHasMoved, double newRangeStart) override
        {
            listPanel.setScroll(newRangeStart / scrollBarThatHasMoved->getMaximumRangeLimit());
            // std::cout << "new range" << newRangeStart << "\n";
        }
    };
}