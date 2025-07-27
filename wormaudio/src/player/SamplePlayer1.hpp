// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "juce_audio_devices/juce_audio_devices.h"
#include "juce_audio_formats/juce_audio_formats.h"

#include <utility>

#include "transport.hpp"

namespace player
{
    class SamplePlayer : public juce::AudioSource
    {
    public:
        virtual void setFile(juce::File&& file) = 0;
        virtual void changeState(TransportState state) = 0;
        // virtual void setTransportCallback(TransportCallback1 callback) = 0;
    };

    class SamplePlayer1 : public SamplePlayer, juce::ChangeListener
    {
        TransportState transportState = STOPPED;
        juce::AudioFormatManager formatManager;
        std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
        juce::AudioTransportSource transportSource;

        TransportCallback1 changeCallback{[](TransportState){}};

    public:
        SamplePlayer1()
        {
            formatManager.registerBasicFormats();
            transportSource.addChangeListener(this);
        }

        void setTransportCallback(TransportCallback1 callback)
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

        void changeState(TransportState state) override
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

        void setFile(juce::File&& file) override
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

