#pragma once

// #include <JuceHeader.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include "SubComponentTest.fwd.h"

// import sample_selector;

//==============================================================================

/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

import sample_selector;
import SamplePlayer;
import AudioContext;

class TestMainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    TestMainComponent();
    ~TestMainComponent() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestMainComponent)

    void updateAngleDelta(double frequency);

    player::AudioContext context;

    juce::Random random;

    juce::Label frequencyLabel;
    juce::Slider frequencySlider;
    juce::Label volumeLabel;
    juce::Slider volumeSlider;

    std::shared_ptr<player::SamplePlayer> player;
    player::SampleSelector sampleSelector;
    std::unique_ptr<SubComponentTest> testPanel;

    float volume = 0;
    double currentAngle = 0;
    double angleDelta = 0;
    double targetFrequency = 0;
    double currentFrequency = 0;
};
