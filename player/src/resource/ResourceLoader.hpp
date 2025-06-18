#pragma once

#include "juce_audio_formats/juce_audio_formats.h"

namespace asset
{
    class ElementSampleBuffer;

    /// Responsible for loading audio files. All Resource instances load their data through here.
    class ResourceLoader
    {
        juce::AudioFormatManager formatManager;

    public:
        // using Ptr = std::shared_ptr<ResourceLoader>;
        using Ptr = ResourceLoader*;

        static Ptr getInstance();

        juce::AudioFormatManager& getFormatManager()
        {
            return formatManager;
        }

        bool loadFile(const juce::File& file, ElementSampleBuffer& destination);

    private:
        ResourceLoader()
        {
            formatManager.registerBasicFormats();
        }
    };
}

