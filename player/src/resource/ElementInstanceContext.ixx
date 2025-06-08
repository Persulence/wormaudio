module;

#include <vector>
#include <memory>

export module element:ElementInstanceContext;

import ElementInstance;
import AudioContext;

namespace element
{
    export class Element;

    export class ElementInstanceContext
    {
    public:
        ElementInstanceContext() = default;

        virtual ElementInstancePtr createInstance(Element &element) = 0;

        virtual ~ElementInstanceContext() = default;
    };
}