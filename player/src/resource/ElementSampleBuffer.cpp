module;

#include <iostream>
#include <memory>

module ElementSampleBuffer;

namespace resource
{
    ElementSampleBuffer::Ptr ElementSampleBuffer::create()
    {
        return std::make_shared<ElementSampleBuffer>();
    }
}
