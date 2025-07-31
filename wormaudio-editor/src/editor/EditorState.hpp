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

#include <filesystem>
#include <string>
#include <unordered_map>
#include <cereal/types/unordered_map.hpp>
#include "serialization/juce_uuid.hpp"

#include "resource/Project.hpp"

namespace editor
{
    using BeforeEditorStateSave = signal_event::Callback<>;

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
        std::unordered_map<resource::UUID, StateNodeData> nodes;

        INTERNAL_SERIALIZE
        {
            cereal::make_optional_nvp(ar, "nodes", nodes);
        }
    };

    class EditorState
    {
    public:
        static constexpr std::string CANVAS_FILENAME = "canvas.json";

        BeforeEditorStateSave::Signal beforeSave;

        void saveState(std::filesystem::path projectDir, const resource::Handle<resource::Project> project) const;
        void loadState(std::filesystem::path projectDir, const resource::Handle<resource::Project> project);

        void saveCanvas(const resource::Handle<event::EventDef> &sound, SoundCanvasData &&data);
        std::optional<SoundCanvasData> getCanvas(const resource::Handle<event::EventDef> &sound);

        void clear();

        static std::filesystem::path getCanvasStateFile(const std::filesystem::path &projectDir);

    private:
        std::unordered_map<resource::UUID, SoundCanvasData> canvasData;

        FRIEND_CEREAL
        INTERNAL_SPLIT_SAVE
        {
            cereal::make_optional_nvp(ar, "canvas_data", canvasData);
        }

        INTERNAL_SPLIT_LOAD
        {
            cereal::make_optional_nvp(ar, "canvas_data", canvasData);
        }
    };
}
