#pragma once

#include <memory>

#include "util/Time.hpp"

namespace element
{
    class Element;

    class ElementInstanceContext
    {
    public:
        ElementInstanceContext() = default;

        virtual ~ElementInstanceContext() = default;

        virtual ElementInstancePtr createInstance(Element &element) = 0;
        virtual void stageHandoff(player::Sample sample) = 0;
    };
}
