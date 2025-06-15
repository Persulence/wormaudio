#include "ChoiceElement.hpp"

#include "juce_audio_basics/juce_audio_basics.h"

import LeanSamplePlayer;
import ElementSampleBuffer;

namespace element
{
    using namespace juce;
    using namespace automation;
    using namespace resource;

    class ChoiceElementInstance : public ElementInstance
    {
        PropertyInstanceContainer properties;
        std::vector<ElementSampleBuffer::Ptr> buffers;
        player::LeanSamplePlayer player;

        Random random;

    public:
        explicit ChoiceElementInstance(const player::AudioContext &context_, const PropertyInstanceContainer &properties_, std::vector<ElementSampleBuffer::Ptr> buffers_) :
            ElementInstance(context_), properties(properties_), buffers(std::move(buffers_))
        {
        }

        void start() override
        {
            const int idx = random.nextInt(buffers.size());
            player.setBuffer(buffers[idx]);

            player.changeState(player::PLAYING);
        }

        void stop() override
        {
            player.changeState(player::STOPPED);
        }

        void getNextAudioBlock(const AudioSourceChannelInfo &bufferToAdd) override
        {
            // TODO continuous sound when clip ends mid-block
            if (player.getState() == player::STOPPED)
            {
                start();
            }

            player.getNextAudioBlock(bufferToAdd);

        }
    };

    // --- ChoiceElement ---

    std::vector<std::shared_ptr<PropertyDef>> ChoiceElement::getProperties()
    {
        return {};
    }

    ElementInstancePtr ChoiceElement::createInstance(player::AudioContext audioContext,
                                                     AutomationRegistryInstance &automation)
    {
        cacheBuffers();

        return std::make_shared<ChoiceElementInstance>(
            audioContext,
            automation.getContainer(shared_from_this()),
            cachedBuffers);
    }

    std::string ChoiceElement::getName()
    {
        return "Choice (" + std::to_string(clips.size()) + " clips)";
    }

    void ChoiceElement::addClip(const Resource::Ptr &resource)
    {
        clips.push_back(resource);
        dirty = true;
    }

    void ChoiceElement::cacheBuffers()
    {
        if (dirty)
        {
            cachedBuffers.clear();
            for (const auto& resource : clips)
            {
                cachedBuffers.push_back(resource->getAudio());
            }

            dirty = false;
        }
    }
}
