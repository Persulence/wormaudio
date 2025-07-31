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

#include <string>
#include <filesystem>

#include "EditorState.hpp"
#include "juce_gui_basics/juce_gui_basics.h"
#include "resource/Project.hpp"

namespace editor
{
    class ProjectSaveManager
    {
    public:
        ProjectSaveManager() = default;

        void saveAuto(const resource::Handle<resource::Project> &project, const EditorState &editorState);

        void saveNewProject();

        void saveAs(resource::Handle<resource::Project> project, const EditorState &editorState);

        void open(EditorState &editorState); // Shows the dialogue
        resource::Handle<resource::Project> open(const std::filesystem::path &path, EditorState &editorState);

        std::filesystem::path getAssetsFolder() const;

        std::filesystem::path lastSavedPath = "";
        // std::future<resource::Handle<resource::Project>> future;

        void activateProject(const resource::Handle<resource::Project> &project);

    private:
        std::unique_ptr<juce::FileChooser> fileChooser;
    };
}
