// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "ProjectSettingsDialogue.hpp"

#include "settings/settings.hpp"

namespace ui
{
    using namespace juce;

    class ProjectSettingsDialogue::BottomPanel : public juce::Component
    {
        editor::Editor &editor;
        juce::TextButton okButton;
        juce::TextButton cancelButton;
        juce::TextButton applyButton;

    public:
        BottomPanel(editor::Editor& editor_):
            editor(editor_)
        {
            addAndMakeVisible(okButton);
            okButton.setButtonText("Ok");

            addAndMakeVisible(cancelButton);
            cancelButton.setButtonText("Cancel");

            addAndMakeVisible(applyButton);
            applyButton.setButtonText("Apply");
        }

        void resized() override
        {
            auto bounds = getLocalBounds();
            FlexBox flexBox;
            flexBox.justifyContent = FlexBox::JustifyContent::spaceBetween;
            flexBox.alignContent = FlexBox::AlignContent::stretch;
            flexBox.flexDirection = FlexBox::Direction::row;
            flexBox.items.add(FlexItem{okButton}.withMinHeight(settings::browserEntryHeight).withMinWidth(settings::buttonWidth).withMaxHeight(settings::browserEntryHeight).withMaxWidth(settings::buttonWidth));
            flexBox.items.add(FlexItem{cancelButton}.withMinHeight(settings::browserEntryHeight).withMinWidth(settings::buttonWidth).withMaxHeight(settings::browserEntryHeight).withMaxWidth(settings::buttonWidth));
            flexBox.items.add(FlexItem{applyButton}.withMinHeight(settings::browserEntryHeight).withMinWidth(settings::buttonWidth).withMaxHeight(settings::browserEntryHeight).withMaxWidth(settings::buttonWidth));
            flexBox.performLayout(getLocalBounds().removeFromRight(250));
        }
    };

    ProjectSettingsDialogue::ProjectSettingsDialogue(editor::Editor &editor_):
        editor(editor_),
        bottomPanel(std::make_unique<BottomPanel>(editor_))
    {
        addAndMakeVisible(bottomPanel.get());
    }

    ProjectSettingsDialogue::~ProjectSettingsDialogue() = default;

    void ProjectSettingsDialogue::paint(juce::Graphics &g)
    {
        paintBackground(g);
    }

    void ProjectSettingsDialogue::resized()
    {
        auto bounds = getLocalBounds();
        bottomPanel->setBounds(bounds.removeFromBottom(30));
    }
}
