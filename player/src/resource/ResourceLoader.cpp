#include "ResourceLoader.hpp"

#include "ElementSampleBuffer.hpp"
#include "util/io.hpp"

namespace asset
{
    bool ResourceLoader::loadFile(const juce::File &file, ElementSampleBuffer &destination)
    {
        if (!io::readFile(file, formatManager, destination, 10))
        {
            juce::Logger::writeToLog(juce::String("Failed to load file ") + file.getFullPathName() + "\n");
            return false;
        }

        return true;
    }

    ResourceLoader::Ptr ResourceLoader::getInstance()
    {
        // static std::mutex mutex;
        // std::lock_guard lock(mutex);

        // I think initialisation of function-local static is thread safe (????)
        static ResourceLoader instance;

        return &instance;
    }
}
