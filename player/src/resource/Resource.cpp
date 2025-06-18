#include "Resource.hpp"

namespace resource
{
    Resource::Resource(ResourceLoader::Ptr loader_, juce::File file_):
        file(std::move(file_)),
        loader(loader_)
    {

    }

    ElementSampleBuffer::Ptr Resource::getAudio()
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
}

