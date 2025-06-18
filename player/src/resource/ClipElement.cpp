#include "ClipElement.hpp"

#include "Asset.hpp"
#include "player/LeanSamplePlayer.hpp"

namespace element
{
    class ClipElementInstance : public ElementInstance
    {
        player::LeanSamplePlayer player;
        automation::PropertyInstanceContainer properties;

        automation::PropertyInstance::OnChanged::Listener gainListener;

        // bool loop;

    public:
        explicit ClipElementInstance(const player::AudioContext &context_, const asset::ElementSampleBuffer::Ptr& audio_, automation::PropertyInstanceContainer properties_,
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

    // --- ClipElement ---

    ElementInstancePtr ClipElement::createInstance(player::AudioContext context,
            automation::AutomationRegistryInstance &automation)
    {
        return std::make_shared<ClipElementInstance>(context, resource->getAudio(), automation.getContainer(shared_from_this()),
                                                     loop.getValue());
    }

    std::string ClipElement::getName()
    {
        return resource->getFile().getFileName().toStdString();
    }
}
