#pragma once
#include "../panel/Panel.hpp"

namespace ui
{
    class FileBrowserPanel : public Panel,
                             public juce::ChangeListener
    {
        juce::TimeSliceThread updateThread;
        juce::WildcardFileFilter filter;
        juce::DirectoryContentsList contents;
        juce::FileListComponent fileList;
        // juce::TableListBox listBox;
        juce::FileBrowserComponent fileBrowser;

    public:

        FileBrowserPanel():
            updateThread("update files"),
            filter(juce::WildcardFileFilter{"*", "*", "Some files?"}),
            contents(&filter, updateThread),
            fileList(contents),
            fileBrowser(
                juce::FileBrowserComponent::FileChooserFlags::openMode
                | juce::FileBrowserComponent::FileChooserFlags::canSelectDirectories
                | juce::FileBrowserComponent::FileChooserFlags::canSelectFiles
                , juce::File("./"), &filter, nullptr)
        {
            updateThread.startThread();
            // addAndMakeVisible(fileList);
            // contents.refresh();
            // contents.addChangeListener(this);
            addAndMakeVisible(fileBrowser);

            // addAndMakeVisible(listBox);
            // listBox.setHeader(std::make_unique<juce::TableHeaderComponent>());
            // listBox.getHeader().addColumn("ooer", 1, 40, 40, 50, 0, 0);
        }
        void paint(juce::Graphics &g) override;
        void resized() override;

        void changeListenerCallback(juce::ChangeBroadcaster *source) override
        {
            std::cout << "changed\n";
        }
    };
}

