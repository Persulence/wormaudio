// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <filesystem>
#include <string>

#include "resource/Project.hpp"

namespace editor
{
    class EditorState
    {
    public:
        static constexpr std::string CANVAS_FILENAME = "canvas.json";

        // explicit EditorState(std::filesystem::path projectDir);

        void saveState(std::filesystem::path projectDir, const resource::Handle<resource::Project> project) const;

        void loadState(std::filesystem::path projectDir, const resource::Handle<resource::Project> project);

        std::filesystem::path getCanvasStateFile(const std::filesystem::path &projectDir) const;

    private:
        FRIEND_CEREAL
        INTERNAL_SPLIT_SAVE
        {

        }

        INTERNAL_SPLIT_LOAD
        {
        }
    };
}
