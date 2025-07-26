// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>
#include <cereal/types/unordered_map.hpp>

#include "resource/Project.hpp"

namespace editor
{

    struct StateNodeData
    {
        int x, y;

        INTERNAL_SERIALIZE
        {
            cereal::make_optional_nvp(ar, "x", x);
            cereal::make_optional_nvp(ar, "y", y);
        }
    };

    struct SoundCanvasData
    {
        std::unordered_map<std::string, StateNodeData> nodes;

        INTERNAL_SERIALIZE
        {
            cereal::make_optional_nvp(ar, "nodes", nodes);
        }
    };

    class EditorState
    {
    public:
        static constexpr std::string CANVAS_FILENAME = "canvas.json";

        void saveState(std::filesystem::path projectDir, const resource::Handle<resource::Project> project) const;
        void loadState(std::filesystem::path projectDir, const resource::Handle<resource::Project> project);

        void saveCanvas(const resource::Handle<event::EventDef> &sound, SoundCanvasData &&data);
        std::optional<SoundCanvasData> getCanvas(const resource::Handle<event::EventDef> &sound);

        void clear();

        static std::filesystem::path getCanvasStateFile(const std::filesystem::path &projectDir);

    private:
        std::unordered_map<resource::Handle<event::EventDef>, SoundCanvasData> canvasData;

        FRIEND_CEREAL
        INTERNAL_SPLIT_SAVE
        {
            // cereal::make_optional_nvp(ar, "canvas_data", canvasData);
        }

        INTERNAL_SPLIT_LOAD
        {
            // cereal::make_optional_nvp(ar, "canvas_data", canvasData);
        }
    };
}
