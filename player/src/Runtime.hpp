#pragma once

#include <memory>
#include "juce_core/juce_core.h"

import Resource;

namespace runtime
{
    inline resource::ResourceLoader::Ptr getResourceLoader()
    {
        return resource::ResourceLoader::getInstance();
    }

    inline resource::Resource::Ptr createResource(juce::File file)
    {
        return std::make_shared<resource::Resource>(getResourceLoader(), file);
    }
}