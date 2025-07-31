// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "AssetLoader.hpp"

#include "ElementSampleBuffer.hpp"
#include "util/io.hpp"

namespace asset
{
    namespace fs = std::filesystem;
    bool AssetLoader::loadLocal(const LocalPath &path, ElementSampleBuffer &destination)
    {
        auto file = getFile(path);
        if (!io::readFile(file, formatManager, destination, 40))
        {
            juce::Logger::writeToLog(juce::String("Failed to load file ") + file.getFullPathName() + "\n");
            return false;
        }

        return true;
    }

    AssetLoader::Ptr AssetLoader::getInstance()
    {
        // static std::mutex mutex;
        // std::lock_guard lock(mutex);

        // I think initialisation of function-local static is thread safe (????)
        static AssetLoader instance;

        return &instance;
    }

    juce::File AssetLoader::getFile(const LocalPath &localPath) const
    {
        fs::path fullPath = assetRoot;

        fullPath /= localPath;

        return juce::File{fullPath.generic_string()};
    }

    LocalPath AssetLoader::localise(const fs::path path) const
    {
        return fs::relative(path, assetRoot).string();
    }
}
