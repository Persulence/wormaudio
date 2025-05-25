#pragma once

#include "EntryBrowserPanel.hpp"

namespace ui
{
    class FileWidget : public juce::Component
    {
        juce::File file;
        juce::Font& font;

    public:
        explicit FileWidget(juce::File file_, juce::Font& font_):
            file(std::move(file_)),
            font(font_)
        {
        }

        ~FileWidget() override = default;

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

