module;

#include <JuceHeader.h>

#include <utility>

#include "../automation/AutomationRegistry.hpp"
#include "../automation/Property.hpp"
#include "automation/AutomationInstance.hpp"

export module ElementTypes;

import element;
import ElementInstance;
import AudioContext;
import SamplePlayer;
import ElementSampleBuffer;
import LeanSamplePlayer;
import io;
import Resource;

namespace element
{
    using Buffer = juce::AudioBuffer<float>;

    class ClipElementInstance : public ElementInstance
    {
        player::LeanSamplePlayer player;
        automation::PropertyInstanceContainer properties;

    public:
        explicit ClipElementInstance(const player::AudioContext &context_, resource::ElementSampleBuffer::Ptr audio_, automation::PropertyInstanceContainer properties):
            ElementInstance(context_),
            player(std::move(audio_)),
            properties(std::move(properties))
        {
            player.prepareToPlay(audioContext.samplesPerBlock, audioContext.sampleRate);
        }

        ~ClipElementInstance() override = default;

        void start() override
        {
            playSound();
        }

        void stop() override
        {
            player.changeState(player::STOPPED);
            released = true;
        }

        void playSound()
        {
            // std::cout << "Playing sound from a " << typeid(this).name() << "!\n";
            player.changeState(player::PLAYING);
        }

        void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToAdd) override
        {
            player.getNextAudioBlock(bufferToAdd);
        }
    };

    export class ClipElement : public Element, public std::enable_shared_from_this<Element>
    {
        resource::Resource::Ptr resource;
        automation::Property volume;

    public:
        explicit ClipElement(resource::Resource::Ptr resource_):
            resource(std::move(resource_)),
            volume(automation::createProperty("volume", 0, automation::Unit::DBFS))
        {
        }

        ElementInstancePtr createInstance(player::AudioContext context, automation::AutomationInstance& automation) override
        {
            return std::make_shared<ClipElementInstance>(context, getAudio(), automation.getContainer(shared_from_this()));
        }

        std::string getName() override
        {
            return resource->getFile().getFileName().toStdString();
        }

        std::vector<automation::Property> getProperties() override
        {
            return {volume};
        }

    private:
        [[nodiscard]] resource::ElementSampleBuffer::Ptr getAudio() const
        {
            return resource->getAudio();
        }
    };
}
