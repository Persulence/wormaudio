#include "ElementSampleBuffer.hpp"

#include <memory>

namespace asset
{
    ElementSampleBuffer::Ptr ElementSampleBuffer::create()
    {
        return std::make_shared<ElementSampleBuffer>();
    }
}
