module;

#include <JuceHeader.h>

export module ElementTypes;

import Element;
import ElementInstance;
import AudioContext;

namespace element
{
    using Buffer = juce::AudioBuffer<float>;

    class ClipElementInstance : public ElementInstance
    {

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

    };

    export class ClipElement : public Element
    {
        [[nodiscard]] std::shared_ptr<ElementInstance> createInstance(player::AudioContext context) const override
        {
            return std::make_shared<ClipElementInstance>(context);
        }
    };
}
