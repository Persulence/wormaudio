module;

#include <JuceHeader.h>

#include <utility>

#include "../automation/AutomationRegistry.hpp"
#include "../automation/Property.hpp"

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
        // resource::ElementSampleBuffer::Ptr audio;

    public:
        explicit ClipElementInstance(const player::AudioContext &context_, resource::ElementSampleBuffer::Ptr audio_):
                ElementInstance(context_),
                player(std::move(audio_))
                // audio(audio_)
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

    export class ClipElement : public Element
    {
        resource::Resource::Ptr resource;
        automation::Property volume;

    public:
        explicit ClipElement(resource::Resource::Ptr resource_):
            resource(std::move(resource_)),
            volume(automation::createProperty("volume", 0, automation::Unit::DBFS))
        {
        }

        [[nodiscard]] ElementInstancePtr createInstance(player::AudioContext context) const override
        {
            return std::make_shared<ClipElementInstance>(context, getAudio());
        }

        std::string getName() override
        {
            return resource->getFile().getFileName().toStdString();
        }

        void regAutomation(automation::AutomationRegistry &registry) const override
        {
            registry.reg(volume);
        }

    private:
        resource::ElementSampleBuffer::Ptr getAudio() const
        {
            return resource->getAudio();
        }
    };
}
