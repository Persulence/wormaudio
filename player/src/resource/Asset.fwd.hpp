#pragma once
#include <memory>

namespace asset
{
    class Asset;
    using AssetHandle = std::shared_ptr<Asset>;

    class AssetManager;

    class ElementSampleBuffer;
    using ElementSampleBufferHandle = std::shared_ptr<ElementSampleBuffer>;
}
