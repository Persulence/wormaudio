#pragma once

#include <JuceHeader.h>

#include "SubComponentTest.fwd.h"

class SubComponentTest: public juce::Component
{
public:
    SubComponentTest();
    ~SubComponentTest() override = default;
    void resized() override;

private:
    juce::TextButton header;
    juce::TextButton footer;
    juce::TextButton sidebar;
};