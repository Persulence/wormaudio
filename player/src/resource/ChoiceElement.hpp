#pragma once

#include <memory>
#include <vector>

#include "Element.hpp"
#include "ElementInstance.hpp"
#include "juce_data_structures/juce_data_structures.h"

#include "Resource.fwd.hpp"
#include "automation/Property.hpp"
#include "automation/instance/AutomationRegistryInstance.hpp"
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

        void addClip(const asset::AssetHandle &resource);

        const std::vector<asset::AssetHandle>& getClips() const { return clips; }

    private:
        void cacheBuffers();

        std::vector<asset::AssetHandle> clips;

        bool dirty{true};
        std::vector<asset::ElementSampleBufferHandle> cachedBuffers;
    };
}
