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
