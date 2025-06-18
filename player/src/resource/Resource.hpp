#pragma once

#include "ElementSampleBuffer.hpp"
#include "Resource.fwd.hpp"
#include "ResourceLoader.hpp"

namespace resource
{
    enum class Settings : int
    {
        LAZY,
        STREAM,
        PRELOAD
    };

    class Resource
    {
        const juce::File file;
        Settings settings{Settings::LAZY};
        const ResourceLoader::Ptr loader;

        ElementSampleBufferHandle buffer = nullptr;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Resource)

    public:
        Resource(ResourceLoader::Ptr loader_, juce::File file_);

        ElementSampleBuffer::Ptr getAudio();

        [[nodiscard]] juce::File getFile() const
        {
            return file;
        }
    };
}

