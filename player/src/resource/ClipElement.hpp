#pragma once

#include <memory>

#include <juce_data_structures/juce_data_structures.h>
#include <juce_audio_basics/juce_audio_basics.h>

#include "Resource.fwd.hpp"
#include "automation/Property.hpp"
#include "automation/instance/AutomationRegistryInstance.hpp"
#include "util/AudioContext.hpp"

import element;
import ElementInstance;

namespace element
{
    class ClipElement : public Element, public std::enable_shared_from_this<ClipElement>
    {
        resource::ResourceHandle resource;

    public:
        juce::Value loop{false};

        explicit ClipElement(resource::ResourceHandle resource_):
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
