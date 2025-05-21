module;

#include <vector>
#include <memory>

export module ElementInstanceContext;

import Element;
import ElementInstance;
import AudioContext;

namespace element
{
    export class ElementInstanceContext
    {
    public:
        virtual ElementInstancePtr createInstance(const Element& element) = 0;

        virtual ~ElementInstanceContext() = default;
    };
}