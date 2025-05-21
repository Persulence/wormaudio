module;

#include <JuceHeader.h>

#include <utility>

export module ElementTypes;

import Element;
import ElementInstance;
import AudioContext;
import SamplePlayer;

namespace element
{
    using Buffer = juce::AudioBuffer<float>;

    class ClipElementInstance : public ElementInstance
    {
        player::SamplePlayer1 player;

    public:
        explicit ClipElementInstance(const player::AudioContext &context_):
                ElementInstance(context_)
        {

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

        }
    };

    export class ClipElement : public Element
    {
        juce::File file;

    public:
        explicit ClipElement(juce::File file_):
            file(std::move(file_))
        {

        }

        [[nodiscard]] ElementInstancePtr createInstance(player::AudioContext context) const override
        {
            return std::make_shared<ClipElementInstance>(context);
        }
    };
}
