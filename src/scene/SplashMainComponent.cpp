// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "SplashMainComponent.hpp"

#include <filesystem>

#include "resource/serialization.hpp"
#include "settings/settings.hpp"

namespace ui
{
    namespace  fs = std::filesystem;

    ProjectListComponent::ProjectListComponent()
    {
        refresh();

        addAndMakeVisible(foundProjectsLabel);
        foundProjectsLabel.setText("Found projects:", juce::dontSendNotification);
        foundProjectsLabel.setFont(foundProjectsLabel.getFont().withStyle(juce::Font::bold));
    }

    void ProjectListComponent::refresh()
    {
        foundProjects.clear();
        auto pwd = fs::current_path();

        for (const auto& entry : fs::directory_iterator(pwd))
        {
            if (fs::is_directory(entry))
            {
                for (const auto& subEntry : fs::directory_iterator(entry))
                {
                    const fs::path path = subEntry;
                    if (path.extension() == resource::FILE_EXTENSION)
                    {
                        // Project found!
                        auto& ptr = foundProjects.emplace_back(std::make_unique<ProjectEntry>(path));
                        addAndMakeVisible(ptr.get());
                    }
                }
            }
        }

        resized();
    }

    void ProjectListComponent::paint(juce::Graphics &g)
    {
        paintBackground(g);
    }

    void ProjectListComponent::resized()
    {
        auto bounds = getLocalBounds();
        foundProjectsLabel.setBounds(bounds.removeFromTop(settings::browserEntryHeight));

        int y = bounds.getY();
        int entryH = settings::browserEntryHeight;
        for (auto& entry : foundProjects)
        {
            entry->setBounds(getX(), y, getWidth(), entryH);
            y += entryH;
        }
    }


    SplashMainComponent::SplashMainComponent():
        projectList()
    {
        addAndMakeVisible(projectList);
    }

    void SplashMainComponent::resized()
    {
        auto bounds = juce::Rectangle<int>{0, 0, 700, 700};
        projectList.setBounds(bounds.withCentre(getLocalBounds().getCentre()));
    }
}
