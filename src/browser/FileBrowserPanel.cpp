#include "FileBrowserPanel.hpp"

#include <memory>
#include <panel/BorderPanel.hpp>

namespace ui
{
    using namespace juce;

    // FileWidget

    void FileWidget::paint(juce::Graphics &g)
    {
        g.setColour(Colours::wheat);
        auto iconBounds = Rectangle{0, 0, getHeight(), getHeight()};
        iconBounds.reduce(2, 2);
        g.fillRect(iconBounds);

        g.setFont(font);

        g.setColour(Colours::black);
        auto nameText = file.getFileName();
        int nameTextW = font.getStringWidth(nameText);
        g.drawText(nameText, getHeight() + 10, 0, nameTextW, getHeight(), Justification::centred);

        auto sizeText = String{file.getSize()};
        int textW = font.getStringWidth(sizeText);
        int textX = getWidth() - 20 - textW;
        g.drawText(sizeText, textX, 0, textW, getHeight(), Justification::centred);

        // getLookAndFeel().drawFileBrowserRow(g, getWidth(), getHeight(), file, file.getFileName(),
        // nullptr, "", "",
        // false,
        // false, 0,
        // parent);
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
        // fileList.setBounds(getLocalBounds());
        // listBox.setBounds(getLocalBounds());
        // fileBrowser.setBounds(getLocalBounds());

        int i = 0;
        int entryH = 30;
        for (auto& element : fileWidgets)
        {
            element->setBounds(0, i * entryH, getWidth(), entryH);

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

            // widget->setBounds(getLocalBounds());
            widget->setBounds(0, i * entryH, getWidth(), entryH);
        }

        repaint();
    }
}
