#pragma once

#include "juce_core/juce_core.h"

namespace ui
{
    inline juce::File loadResource(const std::string &path)
    {
        std::string name = "../res/" + path;
        return juce::File{name};
    }

    inline juce::Image getFileIcon(const juce::File& file)
    {
        if (file.isDirectory())
        {
            return juce::ImageCache::getFromFile(loadResource("icon/folder.png"));
        }
        else
        {
            return juce::ImageCache::getFromFile(loadResource("icon/file.png"));
        }
    }
}