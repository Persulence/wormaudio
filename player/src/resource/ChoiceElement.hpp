#pragma once

import element;
import ElementInstance;
import resource;
import ElementSampleBuffer;

#include <memory>
#include <vector>

#include "automation/Property.hpp"
#include "automation/instance/AutomationRegistryInstance.hpp"
#include "juce_data_structures/juce_data_structures.h"
#include "util/AudioContext.hpp"

namespace element
{
    class ChoiceElement : public Element, public std::enable_shared_from_this<ChoiceElement>
    {
    public:
        juce::Value loop{false};

        [[nodiscard]] std::vector<std::shared_ptr<::automation::PropertyDef>> getProperties() override;

        [[nodiscard]] ElementInstancePtr createInstance(::player::AudioContext,
                automation::AutomationRegistryInstance &automation) override;

        std::string getName() override;

        void addClip(const resource::Resource::Ptr &resource);

        const std::vector<resource::Resource::Ptr>& getClips() const { return clips; }

    private:
        void cacheBuffers();

        std::vector<resource::Resource::Ptr> clips;

        bool dirty{true};
        std::vector<resource::ElementSampleBuffer::Ptr> cachedBuffers;
    };
}
