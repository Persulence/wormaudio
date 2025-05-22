module;

#include <juce_core/juce_core.h>

export module Resource;

import ResourceLoader;
import ElementSampleBuffer;

namespace resource
{
    export enum class Settings : int
    {
        LAZY,
        STREAM,
        PRELOAD
    };

    export class Resource
    {
        const juce::File file;
        Settings settings{Settings::LAZY};
        const ResourceLoader::Ptr loader;

        ElementSampleBuffer::Ptr buffer = nullptr;

        JUCE_DECLARE_NON_COPYABLE(Resource)

    public:
        using Ptr = std::shared_ptr<Resource>;

        Resource(ResourceLoader::Ptr loader_, juce::File file_):
            file(std::move(file_)),
            loader(std::move(loader_))
        {

        }

        ElementSampleBuffer::Ptr getAudio()
        {
            if (buffer == nullptr)
            {
                buffer = ElementSampleBuffer::create();
                if (!loader->loadFile(file, *buffer))
                {
                    buffer = EMPTY_BUFFER;
                }
            }

            return buffer;
        }
    };
}

