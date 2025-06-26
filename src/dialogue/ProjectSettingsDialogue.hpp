#pragma once

#include "editor/Editor.hpp"
#include "util/modal/FakeModalDialogue.hpp"

namespace ui
{
    class ProjectSettingsDialogue : public Panel
    {
    public:
        explicit ProjectSettingsDialogue(editor::Editor& editor_);

        void paint(juce::Graphics &g) override;

    private:
        editor::Editor& editor;
    };
}
