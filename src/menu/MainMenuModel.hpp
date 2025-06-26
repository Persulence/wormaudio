#pragma once

#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    class MainMenuModel : public juce::MenuBarModel
    {
    public:
        juce::StringArray getMenuBarNames() override;

        juce::PopupMenu getMenuForIndex(int topLevelMenuIndex, const juce::String &menuName) override;

        void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;

    };
}
