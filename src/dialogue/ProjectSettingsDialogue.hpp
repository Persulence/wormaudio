#pragma once

#include "editor/Editor.hpp"

namespace ui
{
    class ProjectSettingsDialogue : public Panel
    {
    public:
        explicit ProjectSettingsDialogue(editor::Editor& editor_);
        ~ProjectSettingsDialogue() override;

        void paint(juce::Graphics &g) override;
        void resized() override;

    private:
        class BottomPanel;

        editor::Editor& editor;
        std::unique_ptr<BottomPanel> bottomPanel;
    };
}
