#include "UiMainComponent.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

#include "dialogue/ProjectSettingsDialogue.hpp"
#include "theme/MainLookAndFeel.hpp"
#include "panel/BorderPanel.hpp"
#include "editor/Editor.hpp"
#include "menu/MainMenuModel.hpp"
#include "resource/serialization.hpp"
#include "runtime/Runtime.hpp"

using namespace juce;

namespace ui
{
    UiMainComponent::UiMainComponent(Private):
        menuModel(std::make_unique<MainMenuModel>())
    {
        auto& editor = editor::Editor::getInstance();
        editor.startRuntime();
        editor.getRuntime().connectToDevice();

        addAndMakeVisible(mainScene);

        addAndMakeVisible(menuBar);
        menuBar.setModel(menuModel.get());

        commands()
            .add({Commands::SAVE_PROJECT, [](auto&)
            {

            }})
            .add({Commands::SAVE_PROJECT_AS, [this](auto&)
            {
                // File defFile = File::getCurrentWorkingDirectory().getChildFile("project.proj");
                // File defFile = {File::getCurrentWorkingDirectory().getFullPathName() + "/"};
                fileChooser = std::make_unique<FileChooser>("Choose save location",
                    File::getCurrentWorkingDirectory(),
                    "*.proj",
                    true);
                auto flags = FileBrowserComponent::saveMode | FileBrowserComponent::warnAboutOverwriting | FileBrowserComponent::canSelectFiles;
                fileChooser->launchAsync(flags, [](const FileChooser& chooser)
                {
                    if (const auto file = chooser.getResult(); file != File{})
                    {
                        auto& editor = editor::getInstance();
                        resource::writeStructure(editor.getProject(), file.getFullPathName().toStdString());
                    }
                });
            }})
            .add({Commands::OPEN_PROJECT_SETTINGS, [this](auto&)
            {
                auto& editor = editor::getInstance();
                setFakeModal(std::make_unique<ProjectSettingsDialogue>(editor));
            }})
            .add({Commands::QUIT, [](auto&) { JUCEApplication::getInstance()->quit(); }})
        .finish();
    }

    UiMainComponent::~UiMainComponent()
    {
        menuBar.setModel(nullptr);
        auto& editor = editor::Editor::getInstance();
        editor.shutdown();
    }

    void UiMainComponent::resized()
    {
        FlexBox box;
        box.flexDirection = FlexBox::Direction::column;
        box.justifyContent = FlexBox::JustifyContent::flexStart;
        box.alignContent = FlexBox::AlignContent::stretch;
        box.alignItems = FlexBox::AlignItems::stretch;
        float menuBarHeight = 25;
        box.items.add(FlexItem{menuBar}.withMaxHeight(menuBarHeight).withHeight(menuBarHeight));
        box.items.add(FlexItem{mainScene}.withFlex(2));
        box.performLayout(getLocalBounds());

        if (dialogue)
        {
            dialogue->toFront(true);
            dialogue->setBounds(getLocalBounds());
        }
    }
}

