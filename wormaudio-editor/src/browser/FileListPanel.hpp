// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "EntryListPanel.hpp"
#include "FileDragSource.hpp"

namespace ui
{
    class HeaderWidget : public juce::Component
    {
        juce::Image icon;
        juce::Font font;

    public:
        explicit HeaderWidget(juce::Font font_);
        void mouseDoubleClick(const juce::MouseEvent &event) override;

        void paint(juce::Graphics &g) override;
    };


    class FileWidget : public juce::Component, public FileDragSource, public std::enable_shared_from_this<FileWidget>
    {
    public:
        using Callback = std::function<void(const std::shared_ptr<FileWidget>& source, bool open, juce::File file)>;

    private:
        juce::File file;
        juce::Font font;
        juce::Image icon;
        // juce::Label label;
        bool selected{false};
        Callback callback{[](const auto&, auto, const auto&){}};

    public:
        explicit FileWidget(juce::File file_, juce::Font font_, Callback callback):
            // TimeSliceThread(getName()),
            file(std::move(file_)),
            font(std::move(font_)),
            callback(std::move(callback))
        {
            updateIcon();

            // addAndMakeVisible(label)
        }

        void paint(juce::Graphics &g) override;
        void mouseDrag(const juce::MouseEvent &event) override;
        void mouseDown(const juce::MouseEvent &event) override;
        void mouseDoubleClick(const juce::MouseEvent &event) override;

        void setSelected(bool selected_)
        {
            selected = selected_;
            repaint();
        }

        juce::File getFile() override
        {
            return file;
        }

    private:
        void updateIcon();
    };

    class FileListPanel : public EntryListPanel<FileWidget>,
                             public juce::ChangeListener
    {
        HeaderWidget header;
        // juce::Viewport& viewport;

        juce::TimeSliceThread updateThread;
        juce::WildcardFileFilter filter;
        std::unique_ptr<juce::DirectoryContentsList> contents;

        std::weak_ptr<FileWidget> selected;

    public:
        FileListPanel();
        ~FileListPanel() override;

        void paint(juce::Graphics &g) override;
        void resized() override;
        void changeListenerCallback(juce::ChangeBroadcaster *source) override;

        void setScroll(double fraction);
        void openFile(const juce::File &file);
        void selectWidget(const std::weak_ptr<FileWidget> &widget);

        void changeDirectory(const juce::File &newDirectory)
        {
            contents->setDirectory(newDirectory, true, true);
            scrollFraction = 0;
            // updateVisibilities();
        }

        juce::File currentDirectory() const
        {
            return contents->getDirectory();
        }
    };
}

