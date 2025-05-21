module;

#include <JuceHeader.h>

#include <utility>

export module SamplePlayer;

import transport;

namespace player
{
    export class SamplePlayer : public juce::AudioSource, juce::ChangeListener
    {
        TransportState transportState = STOPPED;
        juce::AudioFormatManager formatManager;
        std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
        juce::AudioTransportSource transportSource;

        TransportCallback changeCallback{[](TransportState){}};

    public:
        SamplePlayer()
        {
            formatManager.registerBasicFormats();
            transportSource.addChangeListener(this);
        }

        void setChangeListener(TransportCallback callback)
        {
            changeCallback = std::move(callback);
        }

        void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
        {
            transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
        }

        void releaseResources() override
        {
            transportSource.releaseResources();
        }

        void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override
        {
            if (readerSource == nullptr)
            {
                bufferToFill.clearActiveBufferRegion();
                return;
            }

            transportSource.getNextAudioBlock(bufferToFill);
        }

        void changeState(TransportState state)
        {
            if (transportState != state)
            {
                this->transportState = state;
                switch (transportState)
                {
                    case STOPPED:
                        // stopButton.setEnabled (false);
                        // playButton.setEnabled (true);
                        transportSource.setPosition (0.0);
                        break;
                    case STARTING:
                        // playButton.setEnabled (false);
                        transportSource.start();
                        break;
                    case PLAYING:
                        // stopButton.setEnabled (true);
                        break;
                    case STOPPING:
                        transportSource.stop();
                        break;
                }

                changeCallback(transportState);
            }
        }

        void setFile(juce::File&& file)
        {
            if (file != juce::File{})
            {
                auto* reader = formatManager.createReaderFor(file);
                if (reader != nullptr)
                {
                    auto newSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
                    transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
                    readerSource.reset(newSource.release());
                }
            }
        }

    private:

        void changeListenerCallback(juce::ChangeBroadcaster *source) override
        {
            if (source == &transportSource)
            {
                if (transportSource.isPlaying())
                    changeState(PLAYING);
                else
                    changeState(STOPPED);

            }
        }
    };
}

