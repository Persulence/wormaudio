module;

#include <juce_audio_formats/juce_audio_formats.h>

export module ResourceLoadContext;

import ElementSampleBuffer;
import io;

namespace resource
{
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
            io::readFile(file, formatManager, destination, 10);

            return true;
        }
    };
}

