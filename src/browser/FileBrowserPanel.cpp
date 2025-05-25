#include "FileBrowserPanel.hpp"

#include "juce_gui_basics/juce_gui_basics.h"
#include <memory>
#include "util/Resources.hpp"

namespace ui
{
    using namespace juce;

    // FileWidget

    void FileWidget::updateIcon()
    {
        if (icon.isNull())
        {
            auto hashCode = (file.getFullPathName() + "_iconCacheSalt").hashCode();
            auto im = ImageCache::getFromHashCode (hashCode);

            if (im.isNull())
                im = getFileIcon(file);

            if (im.isValid())
            {
                icon = im;
                // triggerAsyncUpdate();
                repaint();
            }
        }
    }

    void FileWidget::paint(Graphics &g)
    {
        g.setColour(Colours::wheat);
        auto iconBounds = Rectangle{0, 0, getHeight(), getHeight()};
        iconBounds.reduce(4, 4);
        // g.fillRect(iconBounds);
        if (!icon.isNull())
        {
            g.drawImage(icon, iconBounds.toFloat(), RectanglePlacement::fillDestination, false);
        }

        g.setFont(font);

        g.setColour(Colours::black);
        auto nameText = file.getFileName();
        int nameTextW = font.getStringWidth(nameText);
        g.drawText(nameText, getHeight() + 10, 0, nameTextW, getHeight(), Justification::centred);

        auto sizeText = String{file.getSize()};
        int textW = font.getStringWidth(sizeText);
        int textX = getWidth() - 20 - textW;
        g.drawText(sizeText, textX, 0, textW, getHeight(), Justification::centred);
    }

    // FileBrowserPanel

    ui::FileBrowserPanel::FileBrowserPanel():
        updateThread("update files"),
        filter(juce::WildcardFileFilter{"*", "*", "Some files?"}) {
        // addAndMakeVisible(fileList);
        // contents.refresh();
        // addAndMakeVisible(fileBrowser);

        // addAndMakeVisible(listBox);
        // listBox.setHeader(std::make_unique<juce::TableHeaderComponent>());
        // listBox.getHeader().addColumn("ooer", 1, 40, 40, 50, 0, 0);

        updateThread.startThread(Thread::Priority::low);
        contents = std::make_unique<DirectoryContentsList>(&filter, updateThread);
        contents->addChangeListener(this);

        contents->setDirectory(File::getCurrentWorkingDirectory(), true, true);

        // std::cout << contents->getDirectory().getFullPathName() << "\n";
    }

    FileBrowserPanel::~FileBrowserPanel() = default;

    void ui::FileBrowserPanel::paint(juce::Graphics &g)
    {
        EntryBrowserPanel::paint(g);
    }

    void ui::FileBrowserPanel::resized()
    {
        int i = 0;
        for (auto& element : fileWidgets)
        {
            int h = getEntryHeight(*element);
            element->setBounds(0, i * h, getWidth(), h);

            ++i;
        }
    }

    void FileBrowserPanel::changeListenerCallback(juce::ChangeBroadcaster *source)
    {
        fileWidgets.clear();
        removeAllChildren();

        for (int i = 0; i < contents->getNumFiles(); ++i)
        {
            auto file = contents->getFile(i);
            auto& widget = fileWidgets.emplace_back(std::make_shared<FileWidget>(file, font));
            addAndMakeVisible(widget.get());
        }

        repaint();
    }
}
