#pragma once

#include "ElementSampleBuffer.hpp"
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

        std::shared_ptr<ElementSampleBuffer> buffer = nullptr;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Resource)

    public:
        using Ptr = std::shared_ptr<Resource>;

        Resource(ResourceLoader::Ptr loader_, juce::File file_);

        ElementSampleBuffer::Ptr getAudio();

        [[nodiscard]] juce::File getFile() const
        {
            return file;
        }
    };
}

