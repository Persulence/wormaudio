#pragma once

#include "event/ElementHandle.hpp"

namespace ui
{
    class ElementDragSource
    {
    public:
        virtual event::ElementHandle getHandle() = 0;

        virtual ~ElementDragSource() = default;
    };
}
