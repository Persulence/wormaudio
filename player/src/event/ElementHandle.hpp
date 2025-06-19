#pragma once

#include <memory>

#include "resource/Element.hpp"

namespace event
{
    /**
     * To provide clarity when dealing with elements that have been registered with an event.
     * A function takes an ElementHandle if it requires an element that has been registered.
     */
    class ElementHandle
    {
    public:
        // May change to a weak_ptr
        std::shared_ptr<element::Element> ptr;

        // explicit ElementHandle(std::unique_ptr<element::Element> element):
        //     ptr(std::move(element))
        // {
        //
        // }
        explicit ElementHandle(std::shared_ptr<element::Element> element):
            ptr(std::move(element))
        {

        }

        element::Element* operator->() const
        {
            return ptr.get();
        }

        element::Element& operator*() const
        {
            return *ptr;
        }
    };
}
