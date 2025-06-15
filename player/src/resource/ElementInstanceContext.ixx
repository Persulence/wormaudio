module;

#include <vector>
#include <memory>

#include "util/AudioContext.hpp"

export module element:ElementInstanceContext;

import ElementInstance;

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