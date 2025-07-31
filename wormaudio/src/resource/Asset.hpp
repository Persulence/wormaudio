// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include "util/serialization_util.hpp"

#include "cereal/types/string.hpp"

#include "ElementSampleBuffer.hpp"
#include "Asset.fwd.hpp"
#include "AssetLoader.hpp"
#include "cereal_optional_nvp.h"

// namespace cereal
// {
//     template<>
//     struct LoadAndConstruct<juce::File>
//     {
//         template <class Archive>
//         static void load_and_construct(Archive& ar, cereal::construct<juce::File>& construct)
//         {
//             std::string path;
//             ar(path);
//             construct(juce::String{path});
//         }
//     };
//
//     EXTERNAL_SPLIT_SAVE(juce::File)
//     {
//         ar(m.getFullPathName().toStdString());
//     }
//
//     EXTERNAL_SPLIT_LOAD(juce::File) { }
// }

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
        Settings settings;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Asset)

        void loadFile();

        void preprocess();

        Asset(AssetLoader::Ptr loader_, LocalPath path, Settings settings_);

        ElementSampleBuffer::Ptr getAudio();

        [[nodiscard]] juce::File getFile() const;

        void markUsed(const bool used_) { isUsed = used_; };
        bool used() const { return isUsed; };

    private:
        bool isUsed{false};
        const std::string path;
        const AssetLoader::Ptr loader;

        ElementSampleBufferHandle buffer = nullptr;

        FRIEND_CEREAL

        INTERNAL_SPLIT_SAVE
        {
            ar(
                cereal::make_nvp("file", path),
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

            construct(AssetLoader::getInstance(), path, settings);
        }
    };
}

