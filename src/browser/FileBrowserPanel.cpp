#include "FileBrowserPanel.hpp"

void ui::FileBrowserPanel::paint(juce::Graphics &g)
{
    // paintBackground(g);
    // paintBorder(g);
}

void ui::FileBrowserPanel::resized()
{
    // fileList.setBounds(getLocalBounds());
    // listBox.setBounds(getLocalBounds());
    fileBrowser.setBounds(getLocalBounds());
}
