#include "ElementSampleBuffer.hpp"

#include <memory>

namespace resource
{
    ElementSampleBuffer::Ptr ElementSampleBuffer::create()
    {
        return std::make_shared<ElementSampleBuffer>();
    }
}
