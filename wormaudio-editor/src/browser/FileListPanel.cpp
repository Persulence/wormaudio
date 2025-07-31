// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "FileListPanel.hpp"

#include <memory>
#include <utility>

#include "juce_gui_basics/juce_gui_basics.h"
#include "util/GuiResources.hpp"
#include "editor/Editor.hpp"

namespace ui
{
    using namespace juce;

    // HeaderWidget

    HeaderWidget::HeaderWidget(Font font_):
        icon(ImageCache::getFromFile(loadResource("icon/up_folder.png"))),
        font(std::move(font_))
    {

    }

    void HeaderWidget::mouseDoubleClick(const MouseEvent &event)
    {
        if (const auto parent = findParentComponentOfClass<FileListPanel>())
        {
            parent->changeDirectory(parent->currentDirectory().getParentDirectory());
        }
    }

    void HeaderWidget::paint(Graphics &g)
    {
        g.setColour(Colours::wheat);
        auto iconBounds = juce::Rectangle<int>{0, 0, getHeight(), getHeight()};
        iconBounds.reduce(4, 4);

        if (!icon.isNull())
        {
            g.drawImage(icon, iconBounds.toFloat(), RectanglePlacement::fillDestination, false);
        }

        g.setFont(font);

        g.setColour(getLookAndFeel().findColour(juce::Label::textColourId));
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
        if (selected)
        {
            g.setColour(Colours::darkblue);
            g.fillRect(getLocalBounds());
        }
        auto iconBounds = juce::Rectangle<int>{0, 0, getHeight(), getHeight()};
        iconBounds.reduce(4, 4);
        // g.fillRect(iconBounds);
        if (!icon.isNull())
        {
            g.drawImage(icon, iconBounds.toFloat(), RectanglePlacement::fillDestination, false);
        }

        g.setFont(font);
        g.setColour(selected ? Colours::white : getLookAndFeel().findColour(juce::Label::textColourId));
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

    void FileWidget::mouseDown(const MouseEvent &event)
    {
        callback(shared_from_this(), false, file);
    }

    void FileWidget::mouseDoubleClick(const MouseEvent &event)
    {
        callback(shared_from_this(), true, file);
    }


    // FileBrowserPanel

    FileListPanel::FileListPanel():
        EntryListPanel(1),
        header(font),
        updateThread("update files"),
        filter(WildcardFileFilter{AUDIO_FILE_EXTENSIONS, "*", "Audio files"})
    {

        addAndMakeVisible(header);

        updateThread.startThread(Thread::Priority::low);
        contents = std::make_unique<DirectoryContentsList>(&filter, updateThread);
        contents->addChangeListener(this);

        auto assetsFolder = editor::getInstance().saveManager.getAssetsFolder();
        File file{assetsFolder.generic_string()};
        contents->setDirectory(file, true, true);

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

        // updateVisibilities();

        // setBounds(getBounds().withHeight(getExpectedHeight()));
    }

    void FileListPanel::setScroll(double fraction)
    {
        if (std::floor(scrollFraction * entries.size()) != std::floor(fraction * entries.size()))
        {
            scrollFraction = fraction;
            updateVisibilities();
        }
    }

    void FileListPanel::openFile(const File &file)
    {
        if (file.isDirectory())
        {
            changeDirectory(file);
        }
    }

    void FileListPanel::selectWidget(const std::weak_ptr<FileWidget> &widget)
    {
        if (auto shared = selected.lock())
        {
            shared->setSelected(false);
        }

        selected = widget;

        if (auto shared = selected.lock())
        {
            shared->setSelected(true);
        }
    }

    void FileListPanel::changeListenerCallback(ChangeBroadcaster *source)
    {
        entries.clear();
        removeAllChildren();

        addAndMakeVisible(header);

        for (int i = 0; i < contents->getNumFiles(); ++i)
        {
            auto file = contents->getFile(i);
            auto& widget = entries.emplace_back(std::make_shared<FileWidget>(file, font, [this](const auto& source, bool open, const auto& f)
            {
                if (open)
                {
                    openFile(f);
                }
                else
                {
                    selectWidget(source);
                }
            }));
            addAndMakeVisible(widget.get());
        }

        expectedHeight = (entries.size() + 1) * getEntryHeight();

        setBounds(getBounds().withHeight(getExpectedHeight()));
        resized();
        updateVisibilities();
        repaint();

        callback(entries.size());
    }

}
