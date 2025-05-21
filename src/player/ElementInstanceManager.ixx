module;

#include <JuceHeader.h>

export module ElementInstanceManager;

import Element;
import ElementInstance;
import ElementInstanceContext;
import AudioContext;

namespace player
{
    using namespace element;

    export class ElementInstanceManager : public ElementInstanceContext, public juce::AudioSource
    {
        std::vector<ElementInstancePtr> active;
        AudioContext audioContext;
    public:

        ElementInstancePtr createInstance(const element::Element& element) override
        {
            // tODO: look into reusing identical instances
            return active.emplace_back(element.createInstance(audioContext));
        }

        void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
        {
            audioContext = {samplesPerBlockExpected, sampleRate};
        }

        void releaseResources() override
        {
            audioContext = {};
        }

        void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override
        {
            
        }
    };
}

