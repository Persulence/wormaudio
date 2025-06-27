#pragma once

#include "util/serialization_util.hpp"

#include "ElementSampleBuffer.hpp"
#include "Resource.fwd.hpp"
#include "ResourceLoader.hpp"

namespace cereal
{
    template<>
    struct LoadAndConstruct<juce::File>
    {
        template <class Archive>
        static void load_and_construct(Archive& ar, cereal::construct<juce::File>& construct)
        {
            std::string path;
            ar(path);
            construct(juce::String{path});
        }
    };

    EXTERNAL_SPLIT_SAVE(juce::File)
    {
        ar(m.getFullPathName().toStdString());
    }

    EXTERNAL_SPLIT_LOAD(juce::File) { }
}

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

    public:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Asset)

        Asset(ResourceLoader::Ptr loader_, juce::File file_);

        ElementSampleBuffer::Ptr getAudio();

        [[nodiscard]] juce::File getFile() const
        {
            return file;
        }

    private:
        const juce::File file;
        Settings settings{Settings::LAZY};
        const ResourceLoader::Ptr loader;

        ElementSampleBufferHandle buffer = nullptr;

        FRIEND_CEREAL

        INTERNAL_SERIALIZE
        {
            ar(file);
        }

        LOAD_AND_CONSTRUCT(Asset)
        {
            juce::File file;
            ar(file);
            construct(ResourceLoader::getInstance(), file);
        }
    };
}

