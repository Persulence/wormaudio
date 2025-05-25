#pragma once

#include "EntryBrowserPanel.hpp"

namespace ui
{
    class FileWidget : public juce::Component, juce::TimeSliceThread
    {
        juce::File file;
        juce::Font& font;
        juce::Image icon;

    public:
        explicit FileWidget(juce::File file_, juce::Font& font_):
            TimeSliceThread(getName()),
            file(std::move(file_)),
            font(font_)
        {
            updateIcon();
        }

        ~FileWidget() override = default;

        void updateIcon();

        void paint(juce::Graphics &g);
    };

    class FileBrowserPanel : public EntryBrowserPanel<FileWidget>,
                             public juce::ChangeListener
    {
        juce::TimeSliceThread updateThread;
        juce::WildcardFileFilter filter;
        std::unique_ptr<juce::DirectoryContentsList> contents;

    public:
        FileBrowserPanel();
        ~FileBrowserPanel() override;

        void paint(juce::Graphics &g) override;
        void resized() override;

        void changeListenerCallback(juce::ChangeBroadcaster *source) override;
    };
}

