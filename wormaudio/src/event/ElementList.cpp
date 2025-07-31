
// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "ElementList.hpp"

#include <ranges>

namespace event
{
    ElementHandle ElementList::reg(std::shared_ptr<element::Element> element)
    {
        auto handle = elements.emplace_back(std::move(element));
        automation->reg(handle.ptr);
        onChange.emit();
        return handle;
    }

    void ElementList::unReg(resource::Handle<element::Element> handle)
    {
        if (const auto it = std::ranges::find_if(elements, [&handle](auto& e)
                                                 { return e.ptr == handle; }); it != elements.end())
        {
            automation->removeAll(handle);
            elements.erase(it);
            onChange.emit();
        }
    }

    std::vector<ElementHandle> ElementList::getElements() const
    {
        return elements;
    }

    std::vector<resource::ResourceHandle> ElementList::getChildResources()
    {
        // no std::ranges::to in c++20
        auto result = std::vector<resource::ResourceHandle>{};
        result.resize(elements.size());
        std::ranges::transform(elements, result.begin(), [](auto a){return a.ptr; });
        return result;
    }
}
