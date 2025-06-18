#pragma once

#include <memory>
#include <vector>

#include "Resource.fwd.hpp"
#include "Resource.hpp"
#include "automation/Property.hpp"
#include "automation/instance/AutomationRegistryInstance.hpp"
#include "juce_data_structures/juce_data_structures.h"
#include "util/AudioContext.hpp"

import element;
import ElementInstance;

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

        void addClip(const resource::ResourceHandle &resource);

        const std::vector<resource::ResourceHandle>& getClips() const { return clips; }

    private:
        void cacheBuffers();

        std::vector<resource::ResourceHandle> clips;

        bool dirty{true};
        std::vector<std::shared_ptr<resource::ElementSampleBuffer>> cachedBuffers;
    };
}
