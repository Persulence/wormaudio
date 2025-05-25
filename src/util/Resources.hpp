#pragma once

#include "juce_core/juce_core.h"

namespace ui
{
    inline juce::File loadResource(const std::string &path)
    {
        std::string name = "../res/" + path;
        return juce::File{name};
    }
}