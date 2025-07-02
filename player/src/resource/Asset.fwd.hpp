#pragma once

#include <string>
#include <memory>

namespace asset
{
    using LocalPath = std::string;

    class Asset;
    using AssetHandle = std::shared_ptr<Asset>;

    class AssetManager;

    class ElementSampleBuffer;
    using ElementSampleBufferHandle = std::shared_ptr<ElementSampleBuffer>;
}
