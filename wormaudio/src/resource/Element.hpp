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

#undef Null
#include <util/Data.hpp>

#include "util/serialization_util.hpp"
#include "serialization/cereal_poly_archives.hpp"

#include "ElementInstance.hpp"
#include "SharedResource.hpp"
#include "automation/instance/AutomationRegistryInstance.hpp"
#include "util/AudioContext.hpp"

namespace cereal
{
	template <class Archive, class T>
    std::enable_if_t<traits::is_same_archive<Archive, PortableBinaryInputArchive>::value, bool>
	make_optional_nvp(Archive& ar, const char* name, T&& value)
	{
		ar(make_nvp(name, std::forward<T>(value)));
		return true;
	}
}

namespace element
{
    // Elements are shared resources
    class Element : public resource::SharedResource, public automation::PropertyProvider
    {
    public:
        automation::Property volume{automation::createProperty("volume", 0, automation::Unit::DBFS)};
        util::Data<bool> ignoreChange = true;

        Element() = default;

        [[nodiscard]] virtual ElementInstancePtr createInstance(player::AudioContext, automation::AutomationRegistryInstance& automation) = 0;
        virtual std::string getName() = 0;

        ~Element() override = default;

        // tODO
        bool ignoreStateChange() const { return *ignoreChange; };

        JUCE_DECLARE_NON_COPYABLE(Element)

    private:
        FRIEND_CEREAL

        INTERNAL_SPLIT_SAVE
        {
            // ar(cereal::base_class<SharedResource>(this));
            // ar(cereal::base_class<PropertyProvider>(this));
            ar(cereal::make_nvp("volume", volume));
            ar(cereal::make_nvp("ignore_state_change", ignoreChange));
        }

        INTERNAL_SPLIT_LOAD
        {
            // ar(cereal::base_class<SharedResource>(this));
            // ar(cereal::base_class<PropertyProvider>(this));
            cereal::make_optional_nvp(ar, "volume", volume);
            cereal::make_optional_nvp(ar, "ignore_state_change", ignoreChange);
        }
    };
}