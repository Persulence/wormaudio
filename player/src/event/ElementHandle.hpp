// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <memory>

#include "cereal/cereal.hpp"
#include "cereal/types/memory.hpp"

#include "resource/Element.hpp"
#include "util/serialization_util.hpp"

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


        // Making the serialisation functions private works everywhere else, but not here.
    // private:
        friend class cereal::access;
        ElementHandle() = default;

        INTERNAL_SERIALIZE
        {
            ar(cereal::make_nvp("ptr", ptr));
        }

        // Doesn't work
        // LOAD_AND_CONSTRUCT(ElementHandle)
        // {
        //     std::shared_ptr<element::Element> ptr;
        //     ar(cereal::make_nvp("ptr", ptr));
        //     construct(ElementHandle{ptr});
        // }

    };
}
