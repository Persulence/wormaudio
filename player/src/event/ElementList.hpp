#pragma once
#include <memory>
#include <vector>

#include "ElementHandle.hpp"
#include "automation/AutomationRegistry.hpp"
#include "resource/SharedResource.hpp"
#include "signal/Signal.hpp"

import element;

namespace event
{
    class ElementList : public resource::SharedResource
    {
    public:
        using OnChange = signal_event::Callback<>;
        OnChange::Signal onChange;

        explicit ElementList(automation::AutomationRegistry& automation_):
            automation(automation_)
        {

        }

        /**
         * Associates the given element with the event and registers all automatable properties.
         */
        ElementHandle reg(std::shared_ptr<element::Element> element);

        void unReg(ElementHandle handle);

        [[nodiscard]] std::vector<ElementHandle> getElements() const;

        std::vector<resource::ResourceHandle> getChildResources() override;

    private:
        std::vector<ElementHandle> elements;
        automation::AutomationRegistry& automation;
    };
}
