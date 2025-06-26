#pragma once

#include <string>

#include "juce_gui_basics/juce_gui_basics.h"
#include "resource/Project.hpp"

namespace editor
{
    class ProjectSaveManager
    {
    public:
        ProjectSaveManager() = default;

        void saveAuto(resource::Handle<resource::Project> project);
        void saveAs(resource::Handle<resource::Project> project);

        void open(resource::Handle<resource::Project> project); // Shows the dialogue
        void open(resource::Handle<resource::Project> project, const std::string &path);

        std::string lastSavedPath = "";

    private:
        std::unique_ptr<juce::FileChooser> fileChooser;
    };
}
