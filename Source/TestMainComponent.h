#pragma once

#include <JuceHeader.h>
#include "SubComponentTest.fwd.h"

template <typename T>
class SliderListenerImpl: public juce::SliderListener<T>
{
public:
    using Listener = std::function<void(int v)>;

    SliderListenerImpl() = default;
    ~SliderListenerImpl() override = default;

    void addListener(Listener&& listener);

private:
    void sliderValueChanged(T *) override;
    void sliderDragStarted(T *) override;
    void sliderDragEnded(T *) override;

    std::list<Listener> listeners;
};

//==============================================================================

/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

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

    juce::Random random;

    juce::Label frequencyLabel;
    juce::Slider frequencySlider;
    juce::Label volumeLabel;
    juce::Slider volumeSlider;

    std::unique_ptr<SubComponentTest> testPanel;

    double sampleRate = 0;
    float volume = 0;
    double currentAngle = 0;
    double angleDelta = 0;
    double targetFrequency = 0;
    double currentFrequency = 0;
};

template<typename T>
void SliderListenerImpl<T>::addListener(Listener &&listener)
{
    listeners.emplace_back(std::move(listener));
}

template <typename T>
void SliderListenerImpl<T>::sliderValueChanged(T* slider)
{
    std::cout << "Slider value changed to " << slider->getValue() << std::endl;
    for (auto& listener : listeners)
        listener(slider->getValue());
}

template <typename T>
void SliderListenerImpl<T>::sliderDragStarted(T *slider)
{
}

template <typename T>
void SliderListenerImpl<T>::sliderDragEnded(T *slider)
{
}

enum TransportState
{

};