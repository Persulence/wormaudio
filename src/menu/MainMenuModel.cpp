#include "MainMenuModel.hpp"

#include "command/Commands.hpp"
#include "util/GuiResources.hpp"

namespace ui
{
    using namespace juce;

    StringArray MainMenuModel::getMenuBarNames()
    {
        return {"File", "Edit"};
    }

    PopupMenu MainMenuModel::getMenuForIndex(int topLevelMenuIndex, const juce::String &menuName)
    {
        switch (topLevelMenuIndex)
        {
            case 0:
            {
                PopupMenu menu;
                menu.addCommandItem(&Commands::getInstance(), Commands::NEW_PROJECT.id, {}, std::make_unique<DrawableImage>(
                    getIcon("icon/menu/new.png")));
                menu.addCommandItem(&Commands::getInstance(), Commands::SAVE_PROJECT.id, {}, std::make_unique<DrawableImage>(
                    getIcon("icon/menu/save.png")));
                menu.addCommandItem(&Commands::getInstance(), Commands::SAVE_PROJECT_AS.id, {}, std::make_unique<DrawableImage>(
                    getIcon("icon/menu/save_as.png")));
                menu.addCommandItem(&Commands::getInstance(), Commands::OPEN_PROJECT.id, {}, std::make_unique<DrawableImage>(
                    getIcon("icon/menu/open.png")));
                // menu.addCommandItem(&Commands::getInstance(), Commands::OPEN_PROJECT_SETTINGS.id, {}, std::make_unique<DrawableImage>(
                //     getIcon("icon/menu/project_settings.png")));
                menu.addCommandItem(&Commands::getInstance(), Commands::QUIT.id, {}, std::make_unique<DrawableImage>(
                    getIcon("icon/menu/quit.png")));
                return menu;
            }
            case 1:
            {
                PopupMenu menu;
                return menu;
            }
            default:
            {
                return {};
            }
        }
    }

    void MainMenuModel::menuItemSelected(int menuItemID, int topLevelMenuIndex)
    {
        // std::cout << "Clicked\n";
    }
}
