#pragma once

#include "util/serialization_util.hpp"

#include "ElementSampleBuffer.hpp"
#include "Asset.fwd.hpp"
#include "AssetLoader.hpp"
#include "cereal_optional_nvp.h"

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

    inline AssetLoader::Ptr getResourceLoader()
    {
        return AssetLoader::getInstance();
    }

    class Asset
    {

    public:
        Settings settings{Settings::LAZY};

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Asset)

        void loadFile();

        void preprocess();

        Asset(AssetLoader::Ptr loader_, juce::File file_, Settings settings_);

        ElementSampleBuffer::Ptr getAudio();

        [[nodiscard]] juce::File getFile() const
        {
            return file;
        }

    private:
        const juce::File file;
        const AssetLoader::Ptr loader;

        ElementSampleBufferHandle buffer = nullptr;

        FRIEND_CEREAL

        INTERNAL_SPLIT_SAVE
        {
            ar(
                cereal::make_nvp("file", file.getFullPathName().toStdString()),
                cereal::make_nvp("settings", settings)
                );
        }

        INTERNAL_SPLIT_LOAD { }

        LOAD_AND_CONSTRUCT(Asset)
        {
            std::string path;
            Settings settings;

            ar(cereal::make_nvp("file", path));
            // cereal::make_optional_nvp(ar, "settings", settings);
            ar(cereal::make_nvp("settings", settings));

            construct(AssetLoader::getInstance(), juce::File{path}, settings);
        }
    };
}

