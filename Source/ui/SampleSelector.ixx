module;

#include <JuceHeader.h>

export module sample_selector;

export class SampleSelector : public juce::Component
{
public:
    SampleSelector()
    {
    }

    ~SampleSelector() override = default;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SampleSelector)
};
