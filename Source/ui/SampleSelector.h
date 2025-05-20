#pragma once

#include <JuceHeader.h>

import mtest;

class SampleSelector : public juce::Component
{
public:
    SampleSelector();
    ~SampleSelector() override = default;

private:
    // C c;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SampleSelector)

};
