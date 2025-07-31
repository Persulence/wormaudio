// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once
#include <memory>
#include <utility>
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
        ElementHandle reg(resource::Handle<element::Element> element);

        void unReg(resource::Handle<element::Element> handle);

        [[nodiscard]] std::vector<ElementHandle> getElements() const;

        std::vector<resource::ResourceHandle> getChildResources() override;

    private:
        std::vector<ElementHandle> elements;
        std::shared_ptr<automation::AutomationRegistry> automation; // Has to be shared for serialization. Otherwise, a reference would be sufficient.

        ElementList(decltype(automation) automation_, decltype(elements) elements_):
            elements(std::move(elements_)), automation(std::move(automation_))
        {
            for (auto& element : elements)
            {
                automation->reg(element.ptr);
            }
        }

        FRIEND_CEREAL

        INTERNAL_SERIALIZE
        {
            ar(cereal::make_nvp("elements", elements));
            cereal::make_optional_nvp(ar, "automation", automation);
        }

        LOAD_AND_CONSTRUCT(ElementList)
        {
            decltype(elements) elements;
            decltype(automation) automation;

            ar(cereal::make_nvp("elements", elements));
            ar(cereal::make_nvp("automation", automation));

            construct(automation, elements);
        }
    };
}
