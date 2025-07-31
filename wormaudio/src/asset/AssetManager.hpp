// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include <ranges>
#include <filesystem>

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
        explicit AssetManager(bool autoCreate_):
            autoCreate(autoCreate_)
        {

        }

        AssetHandle get(LocalPath localPath)
        {
            return get(localPath, Settings::PRELOAD);
        }

        AssetHandle get(LocalPath localPath, Settings settings)
        {
            if (const auto it = assets.find(localPath); it != assets.end())
                return it->second;

            if (!autoCreate)
                std::cerr << "New asset creation is not allowed outside editor";

            auto handle = std::make_shared<Asset>(getResourceLoader(), localPath, settings);
            assets.emplace(localPath, handle);
            handle->preprocess();
            return handle;
        }

        void preprocess()
        {
            // TODO: parallel
            for (const auto& asset : assets | std::views::values)
            {
                asset->preprocess();
            }
        }

        void processUnused()
        {
            // TODO: make this work
            std::erase_if(assets, [](const auto& entry)
            {
                return entry.second.use_count() <= 1;
            });
        }

    private:
        std::unordered_map<std::string, AssetHandle> assets;
        bool autoCreate;

        // Serialisation
        AssetManager(const decltype(assets) &assets_, bool autoCreate_):
            assets(assets_),
            autoCreate(autoCreate_)
        {
        }

        FRIEND_CEREAL
        INTERNAL_SERIALIZE
        {
            processUnused();

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
