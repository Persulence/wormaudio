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
        HeaderWidget(juce::Font font);
        void mouseDown(const juce::MouseEvent &event) override;

        void paint(juce::Graphics &g) override;
    };


    class FileWidget : public juce::Component, public FileDragSource
    {
    public:
        using Callback = std::function<void(juce::File)>;

    private:
        juce::File file;
        juce::Font font;
        juce::Image icon;
        Callback callback{[](auto){}};

    public:
        explicit FileWidget(juce::File file_, juce::Font font_, Callback callback):
            // TimeSliceThread(getName()),
            file(std::move(file_)),
            font(std::move(font_)),
            callback(std::move(callback))
        {
            updateIcon();
        }

        void paint(juce::Graphics &g) override;

        void mouseDrag(const juce::MouseEvent &event) override;
        void mouseDoubleClick(const juce::MouseEvent &event) override;

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

    public:
        FileListPanel();
        ~FileListPanel() override;

        void paint(juce::Graphics &g) override;
        void resized() override;
        void changeListenerCallback(juce::ChangeBroadcaster *source) override;

        void updateVisibilities();
        void setScroll(double fraction);
        void openFile(const juce::File &file);

        void changeDirectory(const juce::File &newDirectory) const
        {
            contents->setDirectory(newDirectory, true, true);
        }

        juce::File currentDirectory() const
        {
            return contents->getDirectory();
        }
    };
}

