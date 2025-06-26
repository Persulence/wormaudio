#include "ProjectSaveManager.hpp"

#include "resource/serialization.hpp"

namespace editor
{
    using namespace juce;

    void ProjectSaveManager::save(resource::Handle<resource::Project> project)
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
}
