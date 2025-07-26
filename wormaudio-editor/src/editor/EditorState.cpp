// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "EditorState.hpp"

#include <fstream>

#include "ToastManager.hpp"
#include "resource/serialization.hpp"

namespace editor
{
    void EditorState::saveState(std::filesystem::path projectDir, resource::Handle<resource::Project> project) const
    {
        beforeSave.emit();

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
        // Catch exceptions here as the editor data is not essential for a project to be loaded.
        try
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
        catch (std::exception& e)
        {
            clear();
            ui::ToastManager::getInstance().addMessage(std::format("Failed to load node canvas data: {}", e.what()), ui::ToastManager::WARNING);
        }
    }

    void EditorState::saveCanvas(const resource::Handle<event::EventDef>& sound, SoundCanvasData&& data)
    {
        canvasData.insert_or_assign(sound->getUUID(), data);
    }

    std::optional<SoundCanvasData> EditorState::getCanvas(const resource::Handle<event::EventDef>& sound)
    {
        if (const auto it = canvasData.find(sound->getUUID()); it != canvasData.end())
        {
            return it->second;
        }

        return {};
    }

    void EditorState::clear()
    {
        canvasData.clear();
    }

    std::filesystem::path EditorState::getCanvasStateFile(const std::filesystem::path &projectDir)
    {
        return projectDir / std::filesystem::path{CANVAS_FILENAME};
    }
}
