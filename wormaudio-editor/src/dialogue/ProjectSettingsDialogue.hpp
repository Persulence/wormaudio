// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "editor/Editor.hpp"
#include "panel/Panel.hpp"

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
