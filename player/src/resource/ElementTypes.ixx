module;

#include <JuceHeader.h>

#include <utility>

export module ElementTypes;

import Element;
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
                player(audio_)
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
            released = true;
        }

        void playSound()
        {
            std::cout << "Playing sound from a " << typeid(this).name() << "!\n";
        }

        void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override
        {
            player.getNextAudioBlock(bufferToFill);
        }
    };

    export class ClipElement : public Element
    {
        juce::File file;
        resource::Resource::Ptr resource;

    public:
        explicit ClipElement(juce::File file_, resource::Resource::Ptr resource_):
            file(std::move(file_)),
            resource(std::move(resource_))
        {
        }

        [[nodiscard]] ElementInstancePtr createInstance(player::AudioContext context) const override
        {
            return std::make_shared<ClipElementInstance>(context, getAudio());
        }

    private:
        resource::ElementSampleBuffer::Ptr getAudio() const
        {
            return resource->getAudio();
        }
    };
}
