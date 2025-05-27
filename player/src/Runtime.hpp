#pragma once

#include <memory>
#include "juce_core/juce_core.h"

import Resource;
import event;

namespace runtime
{
    class Runtime;

    inline resource::ResourceLoader::Ptr getResourceLoader()
    {
        return resource::ResourceLoader::getInstance();
    }

    inline resource::Resource::Ptr createResource(juce::File file)
    {
        return std::make_shared<resource::Resource>(getResourceLoader(), file);
    }

    class Runtime
    {
        std::vector<event::EventInstance::Ptr> instances;

    public:
        static Runtime& getInstance()
        {
            static Runtime instance;
            return instance;
        }

        event::EventInstance::Ptr instantiate(const event::Event::Ptr &event);
    };

    inline Runtime& getInstance()
    {
        return Runtime::getInstance();
    }

    event::EventInstance::Ptr instantiate(const event::Event::Ptr& event);

}
