#include "ProjectSaveManager.hpp"

#include "Editor.hpp"
#include "ToastManager.hpp"
#include "asset/AssetManager.hpp"
#include "resource/serialization.hpp"

namespace editor
{
    using namespace juce;

    void save(resource::Handle<resource::Project> project, std::string path)
    {
        try
        {
            resource::writeStructure(project, path);

            std::stringstream ss;
            ss << "Saved project to " << path <<"\n";
            ui::ToastManager::getInstance().addMessage(ss.str(), ui::ToastManager::INFO);
        }
        catch (std::exception& e)
        {
            std::stringstream ss;
            ss << "Failed to save project " << path << ":\n";
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

    void ProjectSaveManager::saveAs(resource::Handle<resource::Project> project)
    {
        fileChooser = std::make_unique<FileChooser>("Choose save location",
            File::getCurrentWorkingDirectory(),
            "*.proj",
            true);

        auto flags = FileBrowserComponent::saveMode | FileBrowserComponent::warnAboutOverwriting | FileBrowserComponent::canSelectFiles;

        fileChooser->launchAsync(flags, [this, project](const FileChooser& chooser)
        {
            if (const auto file = chooser.getResult(); file != File{})
            {
                std::string path = file.getFullPathName().toStdString();

                lastSavedPath = path;

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
            "*.proj",
            true);

        auto flags = FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles;

        fileChooser->launchAsync(flags, [this](const FileChooser& chooser)
        {
            if (const auto file = chooser.getResult(); file != File{})
            {
                const std::string path = file.getFullPathName().toStdString();
                future = open(path);

                fileChooser = nullptr;
                changeProject();
                return;
            }

            // This is concerning, but it's preventing the last file chooser from getting a static lifetime and being picked up by the JUCE leak detector.
            fileChooser = nullptr;
        });

    }

    std::future<resource::Handle<resource::Project>> ProjectSaveManager::open(const std::string &path)
    {
        lastSavedPath = path;

        // auto future = std::async(std::launch::async, [](auto path1) -> resource::Handle<resource::Project>
        // {
        auto project = resource::make<resource::Project>(std::make_unique<asset::AssetManager>(true));
        std::promise<resource::Handle<resource::Project>> promise{};
        promise.set_value(project);
        try
        {
            resource::readStructure(project, path);
            return promise.get_future();
        }
        catch (std::exception& e)
        {
            std::ostringstream msg;

            msg << "Failed to load project " << path << ":\n";
            msg << e.what() << "\n";
            std::cout << msg.str();

            ui::ToastManager::getInstance().addMessage(msg.str(), ui::ToastManager::ERROR);

            return promise.get_future();
        }
            // return project;
        // }, path);

    }

    void ProjectSaveManager::changeProject()
    {
        Editor::getInstance().setProject(future.get());
    }
}
