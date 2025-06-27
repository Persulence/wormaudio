#pragma once

#include <memory>

#include "util/serialization_util.hpp"

#include "ElementInstance.hpp"
#include "SharedResource.hpp"
#include "automation/instance/AutomationRegistryInstance.hpp"
#include "util/AudioContext.hpp"

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
            std::cout << "TODO: volume";
        }

        INTERNAL_SPLIT_LOAD
        {
            std::cout << "TODO: volume";
        }
    };
}