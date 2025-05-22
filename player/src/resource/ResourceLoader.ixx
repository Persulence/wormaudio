module;

#include <juce_audio_formats/juce_audio_formats.h>

export module ResourceLoader;

import ElementSampleBuffer;
import io;

namespace resource
{
    /// Responsible for loading audio files. All Resource instances load their data through here.
    export class ResourceLoader
    {
        juce::AudioFormatManager formatManager;

    public:
        using Ptr = std::shared_ptr<ResourceLoader>;

        ResourceLoader()
        {
            formatManager.registerBasicFormats();
        }

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
    };
}

