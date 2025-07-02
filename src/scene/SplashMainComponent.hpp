#pragma once
#include <filesystem>

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
                std::string fileName = path.filename();

                // addAndMakeVisible(label);
                // label.setText(juce::String{fileName} + " - " + path, juce::dontSendNotification);
                setButtonText(juce::String{fileName} + " - " + path);

                onClick = [this]
                {
                    auto& editor = editor::getInstance();
                    auto future = editor.saveManager.open(path);
                    editor.setProject(future.get());
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
