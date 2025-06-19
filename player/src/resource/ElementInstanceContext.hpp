#pragma once

#include <memory>

namespace element
{
    class Element;

    class ElementInstanceContext
    {
    public:
        ElementInstanceContext() = default;

        virtual ElementInstancePtr createInstance(Element &element) = 0;

        virtual ~ElementInstanceContext() = default;
    };
}