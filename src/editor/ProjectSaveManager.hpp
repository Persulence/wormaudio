// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <string>
#include <filesystem>

#include "juce_gui_basics/juce_gui_basics.h"
#include "resource/Project.hpp"

namespace editor
{
    class ProjectSaveManager
    {
    public:
        ProjectSaveManager() = default;

        void saveAuto(resource::Handle<resource::Project> project);

        void saveNewProject();

        void saveAs(resource::Handle<resource::Project> project);

        void open(); // Shows the dialogue
        resource::Handle<resource::Project> open(const std::filesystem::path &path);

        std::filesystem::path getAssetsFolder() const;

        std::filesystem::path lastSavedPath = "";
        // std::future<resource::Handle<resource::Project>> future;

        void activateProject(const resource::Handle<resource::Project> &project);

    private:
        std::unique_ptr<juce::FileChooser> fileChooser;
    };
}
