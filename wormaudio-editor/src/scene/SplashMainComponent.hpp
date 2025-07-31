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

#pragma once
#include <filesystem>
#include <editor/Editor.hpp>

#include "juce_gui_basics/juce_gui_basics.h"
#include "panel/BorderPanel.hpp"
#include "panel/Panel.hpp"

namespace ui
{
    class ProjectListComponent : public Panel
    {
    public:
        class ProjectEntry : public juce::TextButton
        {
        public:
            ProjectEntry(std::filesystem::path path_):
                path(std::move(path_))
            {
                std::string fileName = path.filename().string();

                // addAndMakeVisible(label);
                // label.setText(juce::String{fileName} + " - " + path, juce::dontSendNotification);
                setButtonText(juce::String{fileName} + " - " + path.string());

                onClick = [this]
                {
                    auto& editor = editor::getInstance();
                    const auto project = editor.saveManager.open(path, editor.getState());
                    editor.saveManager.activateProject(project);
                };
            }

            std::filesystem::path path;
        };

        ProjectListComponent();

        void refresh();

        void paint(juce::Graphics &g) override;
        void resized() override;

    private:
        juce::Label foundProjectsLabel;
        std::vector<std::unique_ptr<ProjectEntry>> foundProjects;
    };

    class SplashMainComponent : public juce::Component
    {
    public:
        SplashMainComponent();
        void resized() override;

        BorderPanel<ProjectListComponent> projectList;
    };
}
