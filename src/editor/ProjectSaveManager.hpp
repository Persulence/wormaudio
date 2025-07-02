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
        resource::Handle<resource::Project> open(const std::string &path);

        std::filesystem::path lastSavedPath = "";
        // std::future<resource::Handle<resource::Project>> future;

    private:
        void changeProject(const resource::Handle<resource::Project> &project);
        std::unique_ptr<juce::FileChooser> fileChooser;
    };
}
