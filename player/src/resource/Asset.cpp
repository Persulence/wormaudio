#include "Asset.hpp"

namespace asset
{
    void Asset::loadFile()
    {
        if (buffer == nullptr)
        {
            buffer = ElementSampleBuffer::create();
            if (!loader->loadFile(file, *buffer))
            {
                buffer = EMPTY_BUFFER;
            }
        }
    }

    void Asset::preprocess()
    {
        if (settings == Settings::PRELOAD)
            loadFile();
    }

    Asset::Asset(const AssetLoader::Ptr loader_, juce::File file_, const Settings settings_):
        settings(settings_),
        file(std::move(file_)),
        loader(loader_)
    {

    }

    ElementSampleBuffer::Ptr Asset::getAudio()
    {
        loadFile();
        return buffer;
    }
}

