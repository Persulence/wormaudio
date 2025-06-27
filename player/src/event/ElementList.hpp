#pragma once
#include <memory>
#include <vector>

#include "util/serialization_util.hpp"
#include "ElementHandle.hpp"
#include "automation/AutomationRegistry.hpp"
#include "resource/SharedResource.hpp"
#include "signal/Signal.hpp"

namespace event
{
    class ElementList : public resource::SharedResource
    {
    public:
        using OnChange = signal_event::Callback<>;
        OnChange::Signal onChange;

        explicit ElementList(std::shared_ptr<automation::AutomationRegistry> automation_):
            automation(std::move(automation_))
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
        std::shared_ptr<automation::AutomationRegistry> automation; // Has to be shared for serialization. Otherwise, a reference would be sufficient.

        PRIVATE_SERIALIZE(ElementList)

        INTERNAL_SERIALIZE
        {
            ar(elements);
        }
    };
}
