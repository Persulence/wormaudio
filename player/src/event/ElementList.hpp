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
        ElementHandle reg(std::shared_ptr<element::Element> element);

        void unReg(ElementHandle handle);

    private:
        std::vector<ElementHandle> elements;
        automation::AutomationRegistry& automation;
    };
}
