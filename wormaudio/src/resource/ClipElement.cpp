// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "ClipElement.hpp"

#include "Asset.hpp"
#include "player/LeanSamplePlayer.hpp"
#include "automation/Property.hpp"
#include "cereal/types/polymorphic.hpp"

namespace element
{
    class ClipElementInstance : public ElementInstance
    {
        player::LeanSamplePlayer player;
        automation::PropertyInstanceContainer properties;

        automation::PropertyInstance::OnChanged::Listener gainListener;
        Element *parent;

        // bool loop;

    public:
        explicit ClipElementInstance(Element* parent, const player::AudioContext &context_, const asset::ElementSampleBuffer::Ptr& audio_, automation::PropertyInstanceContainer properties_,
                                     bool loop_):
            ElementInstance(context_),
            player(audio_, loop_),
            properties(std::move(properties_)),
            parent(parent)
        // loop(loop_)
        {
            player.prepareToPlay(audioContext.samplesPerBlock, audioContext.sampleRate);

            // TODO: ACCESS THESE WITH PROPER KEYS, NOT MAGIC NUMBERS AAARGH
            properties.instances[0]->onChanged.setup(&gainListener, [this](auto val) { player.setGainDb(val); });
            properties.instances[1]->onChanged.setup(&gainListener, [this](auto val) { player.setSpeed(val); });
        }

        ~ClipElementInstance() override = default;

        void start() override
        {
            playSound();
        }

        void stop() override
        {
            player.changeState(player::STOPPING);
            released = true;
        }

        bool isDone() const override
        {
            return player.getState() == player::STOPPED;
        }

        bool canBeFreed() const override
        {
            return isDone() && ElementInstance::canBeFreed();
        }

        void playSound()
        {
            // std::cout << "Playing sound from a " << typeid(this).name() << "!\n";
            player.changeState(player::STARTING);
        }

        void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToAdd) override
        {
            // TODO continuous sound when clip ends mid-block
            // if (player.getState() == player::STOPPED)
            // {
            //     player.changeState(player::PLAYING);
            // }

            player.getNextAudioBlock(bufferToAdd);
            // if (player.getState() == player::STOPPED)
        }

        Element* getParent() override
        {
            return parent;
        }
    };

    // --- ClipElement ---

    ClipElement::ClipElement(asset::AssetHandle resource_):
        asset(std::move(resource_)) {
    }

    ElementInstancePtr ClipElement::createInstance(player::AudioContext context,
                                                   automation::AutomationRegistryInstance &automation)
    {
        return std::make_shared<ClipElementInstance>(this, context, asset->getAudio(), automation.getContainer(shared_from_this()),
                                                     loop.getValue());
    }

    std::string ClipElement::getName()
    {
        return "Clip: " + asset->getFile().getFileName().toStdString();
    }

    asset::AssetHandle ClipElement::getAsset()
    {
        return asset;
    }
}
