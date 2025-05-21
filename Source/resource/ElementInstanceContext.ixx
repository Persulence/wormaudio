module;

#include <vector>
#include <memory>

export module ElementInstanceContext;

import Element;
import ElementInstance;
import AudioContext;

namespace element
{
    export using ElementInstancePtr = std::shared_ptr<ElementInstance>;

    export class ElementInstanceContext
    {
    public:
        virtual ElementInstancePtr createInstance(const element::Element& element) = 0;

        virtual ~ElementInstanceContext() = default;
    };
}