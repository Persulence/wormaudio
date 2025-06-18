#pragma once

#include <memory>

#include <juce_data_structures/juce_data_structures.h>
#include <juce_audio_basics/juce_audio_basics.h>

#include "ElementSampleBuffer.hpp"
#include "Resource.hpp"
#include "automation/Property.hpp"
#include "automation/instance/AutomationRegistryInstance.hpp"
#include "player/LeanSamplePlayer.hpp"
#include "util/AudioContext.hpp"

import element;
import ElementInstance;

namespace element
{
    class ClipElementInstance : public ElementInstance
    {
        player::LeanSamplePlayer player;
        automation::PropertyInstanceContainer properties;

        automation::PropertyInstance::OnChanged::Listener gainListener;

        // bool loop;

    public:
        explicit ClipElementInstance(const player::AudioContext &context_, const resource::ElementSampleBuffer::Ptr& audio_, automation::PropertyInstanceContainer properties_,
                                     bool loop_):
            ElementInstance(context_),
            player(audio_, loop_),
            properties(std::move(properties_))
            // loop(loop_)
        {
            player.prepareToPlay(audioContext.samplesPerBlock, audioContext.sampleRate);

            properties.instances[0]->onChanged.setup(&gainListener, [this](auto val) { player.setGainDb(val); });
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
            // TODO continuous sound when clip ends mid-block
            // if (player.getState() == player::STOPPED)
            // {
            //     player.changeState(player::PLAYING);
            // }

            player.getNextAudioBlock(bufferToAdd);
        }
    };

    class ClipElement : public Element, public std::enable_shared_from_this<ClipElement>
    {
        resource::Resource::Ptr resource;

    public:
        juce::Value loop{false};

        explicit ClipElement(resource::Resource::Ptr resource_):
            resource(std::move(resource_))
        {
        }

        ElementInstancePtr createInstance(player::AudioContext context, automation::AutomationRegistryInstance& automation) override
        {
            return std::make_shared<ClipElementInstance>(context, getAudio(), automation.getContainer(shared_from_this()),
                loop.getValue());
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
