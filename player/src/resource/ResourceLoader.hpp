#pragma once

#include <juce_audio_formats/juce_audio_formats.h>

#include "ElementSampleBuffer.hpp"

import io;

namespace resource
{
    /// Responsible for loading audio files. All Resource instances load their data through here.
    class ResourceLoader
    {

        juce::AudioFormatManager formatManager;

    public:
        // using Ptr = std::shared_ptr<ResourceLoader>;
        using Ptr = ResourceLoader*;

        static ResourceLoader::Ptr getInstance();

        juce::AudioFormatManager& getFormatManager()
        {
            return formatManager;
        }

        bool loadFile(const juce::File& file, ElementSampleBuffer& destination)
        {
            if (!io::readFile(file, formatManager, destination, 10))
            {
                juce::Logger::writeToLog(juce::String("Failed to load file ") + file.getFullPathName() + "\n");
                return false;
            }

            return true;
        }

    private:
        ResourceLoader()
        {
            formatManager.registerBasicFormats();
        }
    };

    inline ResourceLoader::Ptr ResourceLoader::getInstance()
    {
        // static std::mutex mutex;
        // std::lock_guard lock(mutex);

        // I think initialisation of function-local static is thread safe (????)
        static ResourceLoader instance;

        return &instance;
    }
}

