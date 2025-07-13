// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

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
    };

    inline juce::Image getIcon(const std::string& path)
    {
        return juce::ImageCache::getFromFile(loadResource(path));
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