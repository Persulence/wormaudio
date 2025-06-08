
#include "ElementList.hpp"

namespace event
{
    ElementHandle ElementList::reg(std::shared_ptr<element::Element> element)
    {
        auto handle = elements.emplace_back(std::move(element));
        automation.reg(handle.ptr);
        return handle;
    }

    void ElementList::unReg(ElementHandle handle)
    {
        if (const auto it = std::ranges::find_if(elements, [&handle](auto& e)
                                                 { return e.ptr == handle.ptr; }); it != elements.end())
        {
            automation.removeAll(handle.ptr);
            elements.erase(it);
        }
    }
}
