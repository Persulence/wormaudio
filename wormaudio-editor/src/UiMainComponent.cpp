// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "UiMainComponent.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

#include "asset/AssetManager.hpp"
#include "dialogue/ProjectSettingsDialogue.hpp"
#include "editor/Editor.hpp"
#include "menu/MainMenuModel.hpp"
#include "runtime/Runtime.hpp"
#include "scene/MainSceneComponent.hpp"
#include "scene/SplashMainComponent.hpp"

using namespace juce;

namespace ui
{
    UiMainComponent::UiMainComponent(Private):
        mainScene(std::make_unique<SplashMainComponent>()),
        menuModel(std::make_unique<MainMenuModel>())
    {
        auto& editor = editor::Editor::getInstance();
        editor.startRuntime();
        editor.getRuntime().connectToDevice();

        addAndMakeVisible(mainScene.get());

        addAndMakeVisible(menuBar);
        menuBar.setModel(menuModel.get());

        commands()
            .add({Commands::NEW_PROJECT, [](auto&)
            {
                auto& editor = editor::getInstance();
                editor.saveManager.saveNewProject();
            }})
            .add({Commands::SAVE_PROJECT, [](auto&)
            {
                auto& editor = editor::getInstance();
                editor.saveManager.saveAuto(editor.getProject(), editor.getState());
            }})
            .add({Commands::SAVE_PROJECT_AS, [this](auto&)
            {
                auto& editor = editor::getInstance();
                editor.saveManager.saveAs(editor.getProject(), editor.getState());
            }})
            .add({Commands::OPEN_PROJECT, [this](auto&)
            {
                auto& editor = editor::getInstance();
                editor.saveManager.open(editor.getState());
            }})
            // .add({Commands::OPEN_PROJECT_SETTINGS, [this](auto&)
            // {
            //     auto& editor = editor::getInstance();
            //     setFakeModal(std::make_unique<ProjectSettingsDialogue>(editor));
            // }})
            .add({Commands::QUIT, [](auto&) { JUCEApplication::getInstance()->quit(); }})
        .finish();

        Commands::getInstance().getKeyMappings()->addKeyPress(Commands::QUIT.id, KeyPress{'q', ModifierKeys::ctrlModifier, 0});

        Commands::getInstance().getKeyMappings()->addKeyPress(Commands::NEW_PROJECT.id, KeyPress{'n', ModifierKeys::ctrlModifier, 0});
        Commands::getInstance().getKeyMappings()->addKeyPress(Commands::SAVE_PROJECT.id, KeyPress{'s', ModifierKeys::ctrlModifier, 0});
        Commands::getInstance().getKeyMappings()->addKeyPress(Commands::SAVE_PROJECT_AS.id, KeyPress{'s', ModifierKeys::ctrlModifier | ModifierKeys::shiftModifier, 0});
        Commands::getInstance().getKeyMappings()->addKeyPress(Commands::OPEN_PROJECT.id, KeyPress{'o', ModifierKeys::ctrlModifier, 0});
        // Commands::getInstance().getKeyMappings()->addKeyPress(Commands::OPEN_PROJECT_SETTINGS.id, KeyPress{'s', ModifierKeys::ctrlModifier | ModifierKeys::altModifier, 0});

        editor.onProjectRefreshed.setup(&onRefreshed, [this]
        {
            removeChildComponent(mainScene.get());
            mainScene = std::make_unique<MainSceneComponent>();
            addAndMakeVisible(mainScene.get());
            resized();
        });
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
        box.items.add(FlexItem{*mainScene}.withFlex(2));
        box.performLayout(getLocalBounds());

        if (dialogue)
        {
            dialogue->toFront(true);
            dialogue->setBounds(getLocalBounds());
        }
    }

    void UiMainComponent::addToast(std::unique_ptr<Component> toast)
    {
        std::lock_guard lock{toastMutex};

        int yOffset = 0;
        for (auto& t : toasts)
        {
            yOffset += t->getHeight() + 5;
        }

        auto& added = toasts.emplace_back(std::move(toast));
        addAndMakeVisible(*added);
        added->setAlwaysOnTop(true);

        int offset = 30;
        auto p = getLocalBounds().getTopRight() + Point{-offset, offset + yOffset};
        added->setTopRightPosition(p);
    }

    void UiMainComponent::removeToast(Component *toast)
    {
        std::lock_guard lock{toastMutex};

        removeChildComponent(toast);
        std::erase_if(toasts, [toast](auto& a){ return a.get() == toast; });

        // Why does this duplicate the element thousands of times instead of removing it?
        // toasts.erase(std::remove_if(toasts.begin(), toasts.end(), [toast](auto& a){ return a.get() == toast; }), toasts.begin());
    }
}

