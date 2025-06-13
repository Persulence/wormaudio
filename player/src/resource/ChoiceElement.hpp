#pragma once

import element;
import AudioContext;
import ElementInstance;
import Resource;
import ElementSampleBuffer;

#include <memory>
#include <vector>

#include "automation/Property.hpp"
#include "automation/instance/AutomationRegistryInstance.hpp"

namespace element
{
    class ChoiceElement : public Element, public std::enable_shared_from_this<ChoiceElement>
    {
    public:
        [[nodiscard]] std::vector<std::shared_ptr<::automation::PropertyDef>> getProperties() override;

        [[nodiscard]] ElementInstancePtr createInstance(::player::AudioContext,
                automation::AutomationRegistryInstance &automation) override;

        std::string getName() override;

        void addClip(const resource::Resource::Ptr &resource);

    private:
        void cacheBuffers();

        std::vector<resource::Resource::Ptr> clips;

        bool dirty{true};
        std::vector<resource::ElementSampleBuffer::Ptr> cachedBuffers;
    };
}
