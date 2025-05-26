#pragma once

#include "EntryListPanel.hpp"
#include "FileDragSource.hpp"

namespace ui
{
    class FileWidget : public juce::Component, juce::TimeSliceThread, public FileDragSource
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

        void paint(juce::Graphics &g) override;

        void mouseDrag(const juce::MouseEvent &event) override;

    private:
        void updateIcon();
    };

    class FileListPanel : public EntryListPanel<FileWidget>,
                             public juce::ChangeListener
    {
        juce::TimeSliceThread updateThread;
        juce::WildcardFileFilter filter;
        std::unique_ptr<juce::DirectoryContentsList> contents;

    public:
        FileListPanel();
        ~FileListPanel() override;

        void paint(juce::Graphics &g) override;
        void resized() override;

        void changeListenerCallback(juce::ChangeBroadcaster *source) override;
    };
}

