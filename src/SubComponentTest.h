// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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