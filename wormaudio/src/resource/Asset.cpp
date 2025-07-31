// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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

