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
        juce::File file;
        juce::Font font;
        juce::Image icon;

    public:
        explicit FileWidget(juce::File file_, juce::Font font_):
            // TimeSliceThread(getName()),
            file(std::move(file_)),
            font(font_)
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
        void updateVisibilities();

        void setScroll(double fraction);

        void changeDirectory(const juce::File &newDirectory) const
        {
            contents->setDirectory(newDirectory, true, true);
        }

        juce::File currentDirectory() const
        {
            return contents->getDirectory();
        }

        void changeListenerCallback(juce::ChangeBroadcaster *source) override;
    };
}

