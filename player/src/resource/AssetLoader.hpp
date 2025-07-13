// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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

        juce::File getFile(const LocalPath& localPath);
        bool loadLocal(const LocalPath& path, ElementSampleBuffer& destination);

    private:
        std::filesystem::path assetRoot;

        AssetLoader()
        {
            formatManager.registerBasicFormats();
        }
    };
}

