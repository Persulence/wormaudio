module;

#include <JuceHeader.h>

#include <utility>

#include "../automation/Property.hpp"
#include "automation/instance/AutomationRegistryInstance.hpp"

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

        automation::PropertyInstance::OnChanged::Listener gainListener;

    public:
        explicit ClipElementInstance(const player::AudioContext &context_, const resource::ElementSampleBuffer::Ptr& audio_, automation::PropertyInstanceContainer properties_):
            ElementInstance(context_),
            player(std::move(audio_)),
            properties(std::move(properties_))
        {
            player.prepareToPlay(audioContext.samplesPerBlock, audioContext.sampleRate);

            properties.instances[0]->onChanged.setup(&gainListener, [this](auto val){ player.setGainDb(val); });
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

    export class ClipElement : public Element, public std::enable_shared_from_this<ClipElement>
    {
        resource::Resource::Ptr resource;
        bool loop{false};

    public:
        explicit ClipElement(resource::Resource::Ptr resource_):
            resource(std::move(resource_))
        {
        }

        ElementInstancePtr createInstance(player::AudioContext context, automation::AutomationRegistryInstance& automation) override
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
