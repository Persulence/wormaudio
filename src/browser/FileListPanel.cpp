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

    void HeaderWidget::mouseDown(const juce::MouseEvent &event)
    {
        if (auto parent = findParentComponentOfClass<FileListPanel>())
        {
            parent->changeDirectory(parent->currentDirectory().getParentDirectory());
        }
    }

    void HeaderWidget::paint(juce::Graphics &g)
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

    void FileWidget::mouseDrag(const juce::MouseEvent &event)
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

    void FileWidget::mouseDoubleClick(const juce::MouseEvent &event)
    {
    }


    // FileBrowserPanel

    ui::FileListPanel::FileListPanel(Viewport& viewport):
        header(font),
        viewport(viewport),
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

    void ui::FileListPanel::paint(juce::Graphics &g)
    {
        EntryListPanel::paint(g);
    }

    void ui::FileListPanel::resized()
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

        int i = 1;
        for (const auto& element : fileWidgets)
        {
            const auto elementY = element->getBoundsInParent().getY();

            auto viewportArea = viewport.getBounds();
            if (elementY < viewportArea.getY() || elementY > viewportArea.getBottom())
            {
                element->setVisible(false);
                hidden++;
            }
            else
            {
                element->setVisible(true);
                element->setBounds(0, i * h, getWidth(), h);
                visible++;
            }

            ++i;
        }

        std::cout << "visible: " << visible << " hidden " << hidden << "\n";
    }

    void FileListPanel::changeListenerCallback(juce::ChangeBroadcaster *source)
    {
        fileWidgets.clear();
        removeAllChildren();

        addAndMakeVisible(header);

        for (int i = 0; i < contents->getNumFiles(); ++i)
        {
            auto file = contents->getFile(i);
            auto& widget = fileWidgets.emplace_back(std::make_shared<FileWidget>(file, font));
            addAndMakeVisible(widget.get());
        }

        expectedHeight = (fileWidgets.size() + 1) * getEntryHeight();

        setBounds(getBounds().withHeight(getExpectedHeight()));
        resized();
        repaint();
    }

}
