#include "ProjectSettingsDialogue.hpp"

namespace ui
{
    ProjectSettingsDialogue::ProjectSettingsDialogue(editor::Editor &editor_):
        editor(editor_)
    {

    }

    void ProjectSettingsDialogue::paint(juce::Graphics &g)
    {
        paintBackground(g);
    }
}
