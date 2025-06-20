#pragma once

#include "ElementSampleBuffer.hpp"
#include "Resource.fwd.hpp"
#include "ResourceLoader.hpp"

namespace asset
{
    enum class Settings : int
    {
        LAZY,
        STREAM,
        PRELOAD
    };

    inline ResourceLoader::Ptr getResourceLoader()
    {
        return ResourceLoader::getInstance();
    }

    inline AssetHandle createAsset(const juce::File& file)
    {
        return std::make_shared<Asset>(getResourceLoader(), file);
    }

    class Asset
    {
        const juce::File file;
        Settings settings{Settings::LAZY};
        const ResourceLoader::Ptr loader;

        ElementSampleBufferHandle buffer = nullptr;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Asset)

    public:
        Asset(ResourceLoader::Ptr loader_, juce::File file_);

        ElementSampleBuffer::Ptr getAudio();

        [[nodiscard]] juce::File getFile() const
        {
            return file;
        }
    };
}

