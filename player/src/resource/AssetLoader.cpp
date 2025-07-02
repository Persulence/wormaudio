#include "AssetLoader.hpp"

#include "ElementSampleBuffer.hpp"
#include "util/io.hpp"

namespace asset
{
    namespace fs = std::filesystem;
    bool AssetLoader::loadLocal(const LocalPath &path, ElementSampleBuffer &destination)
    {
        auto file = getFile(path);
        if (!io::readFile(file, formatManager, destination, 10))
        {
            juce::Logger::writeToLog(juce::String("Failed to load file ") + file.getFullPathName() + "\n");
            return false;
        }

        return true;
    }

    AssetLoader::Ptr AssetLoader::getInstance()
    {
        // static std::mutex mutex;
        // std::lock_guard lock(mutex);

        // I think initialisation of function-local static is thread safe (????)
        static AssetLoader instance;

        return &instance;
    }

    juce::File AssetLoader::getFile(const LocalPath &localPath)
    {
        fs::path fullPath = assetRoot;

        fullPath /= localPath;

        return juce::File{fullPath.generic_string()};
    }

    LocalPath AssetLoader::localise(const fs::path path) const
    {
        return fs::relative(path, assetRoot);
    }
}
