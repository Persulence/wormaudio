// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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

template <> struct std::hash<event::ElementHandle>
{
    size_t operator()(const event::ElementHandle& o) const noexcept
    {
        constexpr auto h = std::hash<decltype(o.ptr)>{};
        return h(o.ptr);
    }
};
