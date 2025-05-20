#pragma once

#include <JuceHeader.h>

#include "SamplePlayer.fwd.h"

import transport;


class SamplePlayer : public juce::AudioSource, juce::ChangeListener
{
public:
    SamplePlayer();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;
    void changeState(TransportState state);
    void setFile(juce::File&& file);

private:
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

    TransportState transportState = STOPPED;

    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
};
