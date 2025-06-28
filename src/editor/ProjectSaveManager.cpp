#include "ProjectSaveManager.hpp"

#include "Editor.hpp"
#include "ToastManager.hpp"
#include "resource/serialization.hpp"

namespace editor
{
    using namespace juce;

    void ProjectSaveManager::saveAuto(resource::Handle<resource::Project> project)
    {
        if (lastSavedPath.empty())
        {
            saveAs(project);
            return;
        }

        resource::writeStructure(project, lastSavedPath);
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

                resource::writeStructure(project, path);

                lastSavedPath = path;
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
        auto project = resource::make<resource::Project>();
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
