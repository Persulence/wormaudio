#include "ChoiceElement.hpp"

#include <utility>

#include "player/LeanSamplePlayer.hpp"

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
        bool loop;

    public:
        explicit ChoiceElementInstance(const player::AudioContext &context_, PropertyInstanceContainer properties_,
                                       std::vector<ElementSampleBuffer::Ptr> buffers_,
                                       const bool _loop
                                       ) :
            ElementInstance(context_), properties(std::move(properties_)), buffers(std::move(buffers_)), loop(_loop)
        {

        }

        void start() override
        {
            const int idx = random.nextInt(static_cast<int>(buffers.size()));
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
            if (loop && player.getState() == player::STOPPED)
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
            cachedBuffers, loop.getValue());
    }

    std::string ChoiceElement::getName()
    {
        return "Choice (" + std::to_string(clips.size()) + " clips)";
    }

    void ChoiceElement::addClip(const ResourceHandle &resource)
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
