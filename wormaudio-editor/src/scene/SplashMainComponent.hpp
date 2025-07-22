// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
                    const auto project = editor.saveManager.open(path);
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
