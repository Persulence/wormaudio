#pragma once
#include <memory>
#include <vector>

#include "ElementHandle.hpp"
#include "automation/AutomationRegistry.hpp"

import element;

namespace event
{
    class ElementList
    {
    public:
        explicit ElementList(automation::AutomationRegistry& automation):
            automation(automation)
        {

        }

        /**
         * Associates the given element with the event and registers all automatable properties.
         */
        ElementHandle reg(std::unique_ptr<element::Element> element)
        {
            // auto handle = ElementHandle{(std::move(element))};
            auto handle = elements.emplace_back(std::move(element));
            automation.reg(handle.ptr);
            return handle;
        }

        void unReg(ElementHandle handle)
        {
            if (const auto it = std::ranges::find_if(elements, [&handle](auto& e)
                { return e.ptr == handle.ptr; }); it != elements.end())
            {
                automation.removeAll(handle.ptr);
                elements.erase(it);
            }
        }

    private:
        std::vector<ElementHandle> elements;
        automation::AutomationRegistry& automation;
    };
}
