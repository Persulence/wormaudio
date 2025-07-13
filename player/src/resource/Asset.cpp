// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "Asset.hpp"

namespace asset
{
    void Asset::loadFile()
    {
        if (buffer == nullptr)
        {
            buffer = ElementSampleBuffer::create();
            if (!loader->loadLocal(path, *buffer))
            {
                // ???
            }
        }
    }

    void Asset::preprocess()
    {
        if (settings == Settings::PRELOAD)
            loadFile();
    }

    Asset::Asset(const AssetLoader::Ptr loader_, LocalPath path_, const Settings settings_):
        settings(settings_),
        path(std::move(path_)),
        loader(loader_)
    {

    }

    ElementSampleBuffer::Ptr Asset::getAudio()
    {
        loadFile();
        return buffer;
    }

    juce::File Asset::getFile() const
    {
        return loader->getFile(path);
    }
}

