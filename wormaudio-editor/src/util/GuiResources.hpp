// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include <format>

#include "juce_core/juce_core.h"

namespace ui
{
    constexpr std::string resourcePath(const std::string &path)
    {
        std::string name = "../res/" + path;
        return name;
    }

    inline juce::File loadResource(const std::string &path)
    {
        return juce::File{resourcePath(path)};
    }

    inline std::unordered_map<std::string, std::string> extensionIcons = {
        {".wav", resourcePath("icon/audio.png")},
        {".flac", resourcePath("icon/audio.png")},
        {".aiff", resourcePath("icon/audio.png")},
        {".ogg", resourcePath("icon/audio.png")},
        {".mp3", resourcePath("icon/audio.png")},
        {".wma", resourcePath("icon/audio.png")},
    };

    inline juce::Image getIcon(const std::string& path)
    {
        return juce::ImageCache::getFromFile(loadResource(path));

        auto file = loadResource(path);

        auto hashCode = file.hashCode64();
        auto image = juce::ImageCache::getFromHashCode(hashCode);

        if (image.isNull())
        {
            image = juce::ImageFileFormat::loadFrom(file);
            if (image == juce::Image{})
            {
                juce::Logger::writeToLog(std::format("Failed to load icon {}", path));
            }

            juce::ImageCache::addImageToCache(image, hashCode);
        }

        return image;
    }

    inline juce::Image getFileIcon(const juce::File& file)
    {
        if (file.isDirectory())
        {
            return juce::ImageCache::getFromFile(loadResource("icon/folder.png"));
        }
        else
        {
            auto extension = file.getFileExtension().toStdString();
            if (auto it = extensionIcons.find(extension); it != extensionIcons.end())
            {
                return juce::ImageCache::getFromFile(juce::File{it->second});
            }
        }

        return juce::ImageCache::getFromFile(loadResource("icon/file.png"));
    }
}