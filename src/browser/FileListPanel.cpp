#include "FileListPanel.hpp"

#include <memory>

#include "juce_gui_basics/juce_gui_basics.h"
#include "util/GuiResources.hpp"

namespace ui
{
    using namespace juce;

    // HeaderWidget

    HeaderWidget::HeaderWidget(Font font_):
        icon(ImageCache::getFromFile(loadResource("icon/up_folder.png"))),
        font(font_)
    {

    }

    void HeaderWidget::mouseDown(const MouseEvent &event)
    {
        if (auto parent = findParentComponentOfClass<FileListPanel>())
        {
            parent->changeDirectory(parent->currentDirectory().getParentDirectory());
        }
    }

    void HeaderWidget::paint(Graphics &g)
    {
        g.setColour(Colours::wheat);
        auto iconBounds = Rectangle{0, 0, getHeight(), getHeight()};
        iconBounds.reduce(4, 4);

        if (!icon.isNull())
        {
            g.drawImage(icon, iconBounds.toFloat(), RectanglePlacement::fillDestination, false);
        }

        g.setFont(font);

        g.setColour(Colours::black);
        auto folderText = "up";
        int nameTextW = font.getStringWidth(folderText);
        g.drawText(folderText, getHeight() + 10, 0, nameTextW, getHeight(), Justification::centred);
    }


    // FileWidget

    void FileWidget::updateIcon()
    {
        if (icon.isNull())
        {
            // auto hashCode = (file.getFullPathName() + "_iconCacheSalt").hashCode();
            // auto im = ImageCache::getFromHashCode (hashCode);
            auto im = Image{};

            if (im.isNull())
                im = getFileIcon(file);

            if (im.isValid())
            {
                icon = im;
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

    void FileWidget::mouseDrag(const MouseEvent &event)
    {
        auto offset = Point(30, -30);
        DragAndDropContainer::findParentDragContainerFor(this)->startDragging(
                "FILE", this,
                ScaledImage{icon, 2},
                false,
                &offset,
                nullptr
                );

    }

    void FileWidget::mouseDoubleClick(const MouseEvent &event)
    {
        callback(file);
    }


    // FileBrowserPanel

    FileListPanel::FileListPanel():
        header(font),
        updateThread("update files"),
        filter(WildcardFileFilter{"*", "*", "Some files?"})
    {

        addAndMakeVisible(header);

        updateThread.startThread(Thread::Priority::low);
        contents = std::make_unique<DirectoryContentsList>(&filter, updateThread);
        contents->addChangeListener(this);

        contents->setDirectory(File::getCurrentWorkingDirectory(), true, true);

        // std::cout << contents->getDirectory().getFullPathName() << "\n";
    }

    FileListPanel::~FileListPanel() = default;

    void FileListPanel::paint(Graphics &g)
    {
        EntryListPanel::paint(g);
    }

    void FileListPanel::resized()
    {
        const auto h = getEntryHeight();
        header.setBounds(0, 0, getWidth(), h);

        updateVisibilities();

        // setBounds(getBounds().withHeight(getExpectedHeight()));
    }

    void FileListPanel::updateVisibilities()
    {
        const auto h = getEntryHeight();

        int hidden = 0;
        int visible = 0;

        const int offset = std::floor(fileWidgets.size() * std::min(scrollFraction, 1.0));

        int i = 1;
        for (const auto& element : fileWidgets)
        {
            // const auto elementY = element->getBoundsInParent().getY();

            // auto viewportArea = getParentComponent()->getBounds();
            // if (elementY < viewportArea.getY() || elementY > viewportArea.getBottom())
            if (i > offset)  // TODO hide the overflow
            {
                element->setVisible(true);
                element->setBounds(0, (i - offset) * h, getWidth(), h);
                visible++;
            }
            else
            {
                element->setVisible(false);
                hidden++;
            }

            ++i;
        }

        std::cout << "visible: " << visible << " hidden " << hidden << "\n";
    }

    void FileListPanel::setScroll(double fraction)
    {
        if (std::floor(scrollFraction * fileWidgets.size()) != std::floor(fraction * fileWidgets.size()))
        {
            scrollFraction = fraction;
            updateVisibilities();
        }
    }

    void FileListPanel::openFile(const juce::File &file)
    {
        if (file.isDirectory())
        {
            changeDirectory(file);
        }
    }

    void FileListPanel::changeListenerCallback(ChangeBroadcaster *source)
    {
        fileWidgets.clear();
        removeAllChildren();

        addAndMakeVisible(header);

        for (int i = 0; i < contents->getNumFiles(); ++i)
        {
            auto file = contents->getFile(i);
            auto& widget = fileWidgets.emplace_back(std::make_shared<FileWidget>(file, font, [this](auto f){ openFile(f); }));
            addAndMakeVisible(widget.get());
        }

        expectedHeight = (fileWidgets.size() + 1) * getEntryHeight();

        setBounds(getBounds().withHeight(getExpectedHeight()));
        resized();
        repaint();

        callback(fileWidgets.size());
    }

}
