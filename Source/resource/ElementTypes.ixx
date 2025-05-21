module;

#include <JuceHeader.h>

export module ElementTypes;

import Element;
import ElementInstance;

namespace element
{
    using Buffer = juce::AudioBuffer<float>;

    class ClipElementInstance : public ElementInstance
    {
//        std::shared_ptr<Buffer> buffer;
    public:
        ~ClipElementInstance() override = default;

        virtual void activate() override
        {
            playSound();
        }

        void playSound()
        {
            std::cout << "Playing sound from a " << typeid(this).name() << "!\n";
        }
    };

    export class ClipElement : public Element
    {
        std::shared_ptr<ElementInstance> createInstance() const override
        {
            return std::make_shared<ClipElementInstance>();
        }
    };
}
