#include "MainMenuModel.hpp"

namespace ui
{
    using namespace juce;

    StringArray MainMenuModel::getMenuBarNames()
    {
        return {"thing"};
    }

    PopupMenu MainMenuModel::getMenuForIndex(int topLevelMenuIndex, const juce::String &menuName)
    {
        PopupMenu menu;
        menu.addItem("Ooer", []{});
        return menu;
    }

    void MainMenuModel::menuItemSelected(int menuItemID, int topLevelMenuIndex)
    {
        std::cout << "Clicked\n";
    }
}
