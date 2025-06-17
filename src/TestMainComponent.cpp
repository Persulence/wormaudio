#include "../src/TestMainComponent.h"

#include "SubComponentTest.h"
#include "player/LeanSamplePlayer.hpp"

import ElementSampleBuffer;

using namespace player;

//==============================================================================
TestMainComponent::TestMainComponent():
    random(juce::Random{}),
    player(std::make_shared<LeanSamplePlayer>(std::make_shared<resource::ElementSampleBuffer>())),
    sampleSelector(player, [this]() { shutdownAudio(); },
        [this](const int in, const int out) { setAudioChannels(in, out); }),
    testPanel(std::make_unique<SubComponentTest>())
{
    setSize(600, 400);

    // std::function<void(const TestMainComponent&)> f = std::bind(&TestMainComponent::shutdownAudio, this);

    setAudioChannels(0, 2);

    addAndMakeVisible(sampleSelector);

    addAndMakeVisible(frequencySlider);
    frequencySlider.setRange(50, 5000);
    frequencySlider.setTextValueSuffix(" Hz");
    frequencySlider.setValue(500);
    frequencySlider.setSkewFactorFromMidPoint(frequencySlider.getValue());
    frequencySlider.onValueChange = [this]
    {
        if (context.sampleRate > 0)
        {
            targetFrequency = frequencySlider.getValue();
            updateAngleDelta(frequencySlider.getValue());
        }
    };
    targetFrequency = frequencySlider.getValue();
    currentFrequency = targetFrequency;

    addAndMakeVisible(frequencyLabel);
    frequencyLabel.setText("Frequency: ", juce::dontSendNotification);
    frequencyLabel.attachToComponent(&frequencySlider, true);

    addAndMakeVisible(volumeSlider);
    volumeSlider.setRange(0, 1);
    volumeSlider.setTextValueSuffix(" ");
    volumeSlider.onValueChange = [this]
    {
        if (context.sampleRate > 0)
        {
            volume = static_cast<float>(volumeSlider.getValue());
        }
    };

    addAndMakeVisible(volumeLabel);
    volumeLabel.setText("Volume: ", juce::dontSendNotification);
    volumeLabel.attachToComponent(&volumeSlider, true);

    // addAndMakeVisible(*testPanel);
}

TestMainComponent::~TestMainComponent()
{
    shutdownAudio();
}

void TestMainComponent::prepareToPlay(const int samplesPerBlockExpected, const double sampleRate_)
{
    context = {samplesPerBlockExpected, sampleRate_};

    juce::String message;
    message << "Preparing to play audio...\n";
    message << " samplesPerBlockExpected = " << samplesPerBlockExpected << "\n";
    message << " sampleRate = " << context.sampleRate;
    juce::Logger::writeToLog(message);

    player->prepareToPlay(samplesPerBlockExpected, context.sampleRate);
}

void TestMainComponent::releaseResources()
{
    player->releaseResources();
    juce::Logger::writeToLog("Releasing resources");
}

void TestMainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill)
{
    player->getNextAudioBlock(bufferToFill);

    // auto* leftBuffer = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
    // auto* rightBuffer = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);

    // if (!juce::approximatelyEqual(targetFrequency, currentFrequency))
    // {
    //     auto frequencyIncrement = (targetFrequency - currentFrequency) / bufferToFill.numSamples;
    //     for (int i = 0; i < bufferToFill.numSamples; i++)
    //     {
    //         currentFrequency = currentFrequency + frequencyIncrement;
    //         updateAngleDelta(currentFrequency);
    //
    //         auto value = static_cast<float>(volume * std::sin(currentAngle));
    //         currentAngle += angleDelta;
    //
    //         leftBuffer[i] = value;
    //         rightBuffer[i] = value;
    //     }
    // }
    // else
    // {
    //     for (int i = 0; i < bufferToFill.numSamples; i++)
    //     {
    //         auto value = static_cast<float>(volume * std::sin(currentAngle));
    //         currentAngle += angleDelta;
    //
    //         leftBuffer[i] = value;
    //         rightBuffer[i] = value;
    //     }
    // }
}

//==============================================================================
void TestMainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font {juce::FontOptions{16.0f}});
    g.setColour(juce::Colours::white);
    g.drawText("Hello there!", getLocalBounds(), juce::Justification::centred, true);
}

void TestMainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    auto sliderLeft = 120;
    frequencySlider.setBounds (sliderLeft, 20, getWidth() - sliderLeft - 10, 20);
    volumeSlider.setBounds (sliderLeft, 50, getWidth() - sliderLeft - 10, 20);

    // testPanel->setBounds(0, 100, getWidth(), getHeight() - 100);
    sampleSelector.setBounds(0, 100, getWidth(), getHeight());
}

void TestMainComponent::updateAngleDelta(double frequency)
{
    double cyclesPerSample = frequency / context.sampleRate;
    angleDelta = cyclesPerSample * 2 * juce::MathConstants<double>::pi;
}