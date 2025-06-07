#pragma once
#include <memory>
#include <vector>

#include "ElementHandle.hpp"

import element;

namespace event
{
    class ElementList
    {
    public:
        ElementHandle reg(std::unique_ptr<element::Element> element)
        {
            // auto handle = ElementHandle{(std::move(element))};
            return elements.emplace_back(std::move(element));
        }

    private:
        std::vector<ElementHandle> elements;
    };
}
