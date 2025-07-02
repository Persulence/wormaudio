#include "AssetLoader.hpp"

#include "ElementSampleBuffer.hpp"
#include "util/io.hpp"

namespace asset
{
    bool AssetLoader::loadFile(const juce::File &file, ElementSampleBuffer &destination)
    {
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
}
