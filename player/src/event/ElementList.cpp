
#include "ElementList.hpp"

#include <ranges>

namespace event
{
    ElementHandle ElementList::reg(std::shared_ptr<element::Element> element)
    {
        auto handle = elements.emplace_back(std::move(element));
        automation.reg(handle.ptr);
        onChange.emit();
        return handle;
    }

    void ElementList::unReg(ElementHandle handle)
    {
        if (const auto it = std::ranges::find_if(elements, [&handle](auto& e)
                                                 { return e.ptr == handle.ptr; }); it != elements.end())
        {
            automation.removeAll(handle.ptr);
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
