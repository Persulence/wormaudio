#pragma once

#include <memory>

#include <juce_data_structures/juce_data_structures.h>
#include <juce_audio_basics/juce_audio_basics.h>

#include "Element.hpp"
#include "ElementInstance.hpp"
#include "Resource.fwd.hpp"
#include "automation/Property.hpp"
#include "automation/instance/AutomationRegistryInstance.hpp"
#include "util/AudioContext.hpp"

namespace element
{
    class ClipElement : public Element, public std::enable_shared_from_this<ClipElement>
    {
        asset::AssetHandle resource;

    public:
        util::Data<bool> loop{false};

        explicit ClipElement(asset::AssetHandle resource_):
            resource(std::move(resource_))
        {
        }

        ElementInstancePtr createInstance(player::AudioContext context, automation::AutomationRegistryInstance& automation) override;

        std::string getName() override;

        std::vector<automation::Property> getProperties() override
        {
            return {volume};
        }
    };
}
