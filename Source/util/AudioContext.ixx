module;

export module AudioContext;

namespace player
{
    export struct AudioContext
    {
        int samplesPerBlock;
        double sampleRate;
        bool initialised{false};

        AudioContext():
            samplesPerBlock(0),
            sampleRate(0),
            initialised(false)
        {}

        AudioContext(int samplesPerBlock_, double sampleRate_):
            samplesPerBlock(samplesPerBlock_),
            sampleRate(sampleRate_),
            initialised(true)
        {}
    };
}
