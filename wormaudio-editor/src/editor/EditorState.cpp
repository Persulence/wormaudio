// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "EditorState.hpp"

#include <fstream>
#include "resource/serialization.hpp"

namespace editor
{
    void EditorState::saveState(std::filesystem::path projectDir, resource::Handle<resource::Project> project) const
    {
        {
            const auto filePath = getCanvasStateFile(projectDir);
            std::fstream ostream{filePath, std::ios::out};
            {
                cereal::JSONOutputArchive archive{ostream};
                archive(*this);
            }
            ostream.close();
        }
    }

    void EditorState::loadState(std::filesystem::path projectDir, resource::Handle<resource::Project> project)
    {
        {
            const auto filePath = getCanvasStateFile(projectDir);
            std::fstream istream{filePath, std::ios::in};

            if (!istream.good())
            {
                throw resource::IOException{std::format("File invalid: {}", filePath.string())};
            }

            {
                cereal::JSONInputArchive archive{istream};
                archive(*this);
            }

            istream.close();
        }
    }

    std::filesystem::path EditorState::getCanvasStateFile(const std::filesystem::path &projectDir) const
    {
        return projectDir / std::filesystem::path{CANVAS_FILENAME};
    }
}
