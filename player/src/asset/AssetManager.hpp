#pragma once

#include <ranges>

#include "cereal/types/string.hpp"
#include "cereal/types/unordered_map.hpp"
#include "cereal/types/memory.hpp"

#include "resource/Asset.hpp"
#include "util/serialization_util.hpp"

namespace asset
{
    /// Holds assets referenced by the project.
    /// It's the asset loader's job to load them when required.
    class AssetManager
    {
    public:
        AssetManager(bool autoCreate_):
            autoCreate(autoCreate_)
        {

        }

        AssetHandle get(juce::File file)
        {
            return get(file, Settings::PRELOAD);
        }

        AssetHandle get(juce::File file, Settings settings)
        {
            std::string path = file.getFullPathName().toStdString();

            if (const auto it = assets.find(path); it != assets.end())
                return it->second;

            if (!autoCreate)
                std::cerr << "New asset creation is not allowed outside editor";

            auto handle = std::make_shared<Asset>(getResourceLoader(), file, settings);
            assets.emplace(path, handle);
            handle->preprocess();
            return handle;
        }

        void preload()
        {
            // TODO: parallel
            for (const auto& asset : assets | std::views::values)
            {
                asset->preprocess();
            }
        }

    private:
        std::unordered_map<std::string, AssetHandle> assets;
        bool autoCreate;

        // Serialisation
        AssetManager(const decltype(assets) &assets_, bool autoCreate_):
            assets(assets_),
            autoCreate(autoCreate_)
        {
            preload();
        }

        FRIEND_CEREAL
        INTERNAL_SERIALIZE
        {
            ar(cereal::make_nvp("assets", assets));
            ar(cereal::make_nvp("autoCreate", autoCreate));
        }

        LOAD_AND_CONSTRUCT(AssetManager)
        {
            decltype(assets) assets;
            decltype(autoCreate) autoCreate;

            ar(cereal::make_nvp("assets", assets));
            ar(cereal::make_nvp("autoCreate", autoCreate));

            construct(assets, autoCreate);
        }
    };
}
