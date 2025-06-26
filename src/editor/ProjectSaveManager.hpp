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

        void save(resource::Handle<resource::Project> project);
        void saveAs(resource::Handle<resource::Project> project);

        std::string lastSavedPath = "";

    private:
        std::unique_ptr<juce::FileChooser> fileChooser;
    };
}
