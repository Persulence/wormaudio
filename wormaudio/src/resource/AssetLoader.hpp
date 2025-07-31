// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include "resource/Asset.fwd.hpp"

#include <filesystem>

#include "juce_audio_formats/juce_audio_formats.h"

namespace asset
{
    class ElementSampleBuffer;

    /// Responsible for converting internal paths into global ones. All Resource instances load their data through here.
    class AssetLoader
    {
        juce::AudioFormatManager formatManager;

    public:
        // using Ptr = std::shared_ptr<ResourceLoader>;
        using Ptr = AssetLoader*;

        static Ptr getInstance();
        void setAssetRoot(std::filesystem::path path) { assetRoot = path; }

        juce::AudioFormatManager& getFormatManager()
        {
            return formatManager;
        }

        LocalPath localise(const std::filesystem::path path) const;

        juce::File getFile(const LocalPath& localPath) const;
        bool loadLocal(const LocalPath& path, ElementSampleBuffer& destination);

    private:
        std::filesystem::path assetRoot;

        AssetLoader()
        {
            formatManager.registerBasicFormats();
        }
    };
}

