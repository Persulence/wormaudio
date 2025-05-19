#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent():
    random(juce::Random{})
{
    setSize(600, 400);

    // auto openButton = juce::
    // addAndMakeVisible(&openButton)
    setAudioChannels(0, 2);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay(const int samplesPerBlockExpected, const double sampleRate)
{
    juce::String message;
    message << "Preparing to play audio...\n";
    message << " samplesPerBlockExpected = " << samplesPerBlockExpected << "\n";
    message << " sampleRate = " << sampleRate;
    juce::Logger::getCurrentLogger()->writeToLog (message);

    this->sampleRate = sampleRate;
}

void MainComponent::releaseResources()
{
    std::cout << "release\n";
    juce::Logger::getCurrentLogger()->writeToLog("Releasing resources");
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill)
{
    for (int i = bufferToFill.startSample; i < bufferToFill.numSamples; i++)
    {
        const float value = random.nextFloat() * 0.25 - 0.125;
        bufferToFill.buffer->setSample(0, i, value);
        bufferToFill.buffer->setSample(1, i, value);
    }
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font (16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
