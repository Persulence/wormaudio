// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "ProjectSaveManager.hpp"

#include <filesystem>

#include "Editor.hpp"
#include "ToastManager.hpp"
#include "asset/AssetManager.hpp"
#include "resource/serialization.hpp"

namespace editor
{
    using namespace juce;
    namespace fs = std::filesystem;

    void save(const resource::Handle<resource::Project> &project, const std::filesystem::path &projectFilePath)
    {
        try
        {
            auto projectFolder = projectFilePath.parent_path();

            std::filesystem::create_directory(projectFolder);

            resource::writeStructure(project, projectFilePath);

            std::stringstream ss;
            ss << "Saved project to " << projectFilePath <<"\n";
            ui::ToastManager::getInstance().addMessage(ss.str(), ui::ToastManager::INFO);
        }
        catch (std::exception& e)
        {
            std::stringstream ss;
            ss << "Failed to save project " << projectFilePath << ":\n";
            ss << e.what() << "\n";
            std::cout << ss.str();
            ui::ToastManager::getInstance().addMessage(ss.str(), ui::ToastManager::ERROR);
        }
    }

    void ProjectSaveManager::saveAuto(resource::Handle<resource::Project> project)
    {
        if (lastSavedPath.empty())
        {
            saveAs(project);
            return;
        }

        save(project, lastSavedPath);
    }

    std::string validatePath(fs::path path)
    {
        if (fs::exists(path)
            && !fs::is_directory(path)
            && path.extension() == resource::FILE_EXTENSION)
        {
            // Overwrite existing project
            return path;
        }
        else
        {
            // Assume a folder with the project's name and put the project file inside that.
            std::string name = path.filename();
            // return path.append("/").append(name).append(resource::FILE_EXTENSION);
            return path / (name.append(resource::FILE_EXTENSION));
        }
    }

    void ProjectSaveManager::saveNewProject()
    {
        fileChooser = std::make_unique<FileChooser>("Choose location for new project",
            File::getCurrentWorkingDirectory(),
            String{"*"},
            true);

        auto flags = FileBrowserComponent::saveMode
            | FileBrowserComponent::warnAboutOverwriting
            | FileBrowserComponent::canSelectFiles
            | FileBrowserComponent::canSelectDirectories;

        fileChooser->launchAsync(flags, [this](const FileChooser& chooser)
        {
            if (const auto file = chooser.getResult(); file != File{})
            {
                const std::string chosenPath = file.getFullPathName().toStdString();

                const auto fileName = file.getFileName().toStdString();

                lastSavedPath = validatePath(chosenPath);

                auto project = resource::make<resource::Project>(std::make_unique<asset::AssetManager>(true));

                save(project, lastSavedPath);
                activateProject(project);
            }

            // This is concerning, but it's preventing the last file chooser from getting a static lifetime and being picked up by the JUCE leak detector.
            fileChooser = nullptr;
        });
    }

    void ProjectSaveManager::saveAs(resource::Handle<resource::Project> project)
    {
        fileChooser = std::make_unique<FileChooser>("Choose save location",
            File::getCurrentWorkingDirectory(),
            String{"*"},
            true);

        auto flags = FileBrowserComponent::saveMode
            | FileBrowserComponent::warnAboutOverwriting
            | FileBrowserComponent::canSelectFiles
            | FileBrowserComponent::canSelectDirectories;

        fileChooser->launchAsync(flags, [this, project](const FileChooser& chooser)
        {
            if (const auto file = chooser.getResult(); file != File{})
            {
                const std::string chosenPath = file.getFullPathName().toStdString();

                const auto fileName = file.getFileName().toStdString();

                lastSavedPath = validatePath(chosenPath);

                save(project, lastSavedPath);
            }

            // This is concerning, but it's preventing the last file chooser from getting a static lifetime and being picked up by the JUCE leak detector.
            fileChooser = nullptr;
        });
    }

    void ProjectSaveManager::open()
    {
        fileChooser = std::make_unique<FileChooser>("Choose project to load",
            File::getCurrentWorkingDirectory(),
            String{"*"} + resource::FILE_EXTENSION,
            true);

        auto flags = FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles;

        fileChooser->launchAsync(flags, [this](const FileChooser& chooser)
        {
            if (const auto file = chooser.getResult(); file != File{})
            {
                const fs::path path = file.getFullPathName().toStdString();
                auto project = open(path);

                fileChooser = nullptr;
                activateProject(project);
                return;
            }

            // This is concerning, but it's preventing the last file chooser from getting a static lifetime and being picked up by the JUCE leak detector.
            fileChooser = nullptr;
        });

    }

    resource::Handle<resource::Project> ProjectSaveManager::open(const fs::path &path)
    {
        lastSavedPath = path;

        auto project = resource::make<resource::Project>(std::make_unique<asset::AssetManager>(true));
        try
        {
            resource::readStructure(project, path);
            return project;
        }
        catch (std::exception& e)
        {
            std::ostringstream msg;

            msg << "Failed to load project " << path << ":\n";
            msg << e.what() << "\n";
            std::cout << msg.str();

            ui::ToastManager::getInstance().addMessage(msg.str(), ui::ToastManager::ERROR);

            return project;
        }
    }

    fs::path ProjectSaveManager::getAssetsFolder() const
    {
        return lastSavedPath.parent_path() / "asset";
    }

    void ProjectSaveManager::activateProject(const resource::Handle<resource::Project> &project)
    {
        // Ensure that the asset folder exists
        std::filesystem::create_directory(getAssetsFolder());

        Editor::getInstance().setProject(project);
    }
}
