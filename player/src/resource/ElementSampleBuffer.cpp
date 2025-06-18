#include "ElementSampleBuffer.hpp"

#include <memory>

namespace resource
{
    ElementSampleBuffer::Ptr ElementSampleBuffer::create()
    {
        return std::make_shared<ElementSampleBuffer>();
    }

    const std::shared_ptr<ElementSampleBuffer> EMPTY_BUFFER = std::make_shared<ElementSampleBuffer>();
}
