#pragma once
#include <memory>

namespace resource
{
    class Resource;
    using ResourceHandle = std::shared_ptr<Resource>;

    class ElementSampleBuffer;
    using ElementSampleBufferHandle = std::shared_ptr<ElementSampleBuffer>;
}
