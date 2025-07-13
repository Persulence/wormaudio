// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <memory>

#undef Null
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

        Element() = default;

        [[nodiscard]] virtual ElementInstancePtr createInstance(player::AudioContext, automation::AutomationRegistryInstance& automation) = 0;
        virtual std::string getName() = 0;

        ~Element() override = default;
        JUCE_DECLARE_NON_COPYABLE(Element)

    private:
        FRIEND_CEREAL

        INTERNAL_SPLIT_SAVE
        {
            // ar(cereal::base_class<SharedResource>(this));
            // ar(cereal::base_class<PropertyProvider>(this));
            ar(cereal::make_nvp("volume", volume));
        }

        INTERNAL_SPLIT_LOAD
        {
            // ar(cereal::base_class<SharedResource>(this));
            // ar(cereal::base_class<PropertyProvider>(this));
            cereal::make_optional_nvp(ar, "volume", volume);
        }
    };
}