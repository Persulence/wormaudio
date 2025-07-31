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
