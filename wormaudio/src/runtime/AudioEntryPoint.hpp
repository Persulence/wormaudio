// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <cassert>
#include <juce_audio_devices/juce_audio_devices.h>

namespace runtime
{
    class AudioEntryPoint : public juce::AudioSource
    {
        juce::AudioDeviceManager deviceManager;
        juce::AudioSourcePlayer sourcePlayer;

    public:
        ~AudioEntryPoint() override
        {
            assert(sourcePlayer.getCurrentSource() == nullptr);
        }

    protected:
        void start()
        {
            // auto setup = deviceManager.getAudioDeviceSetup();
            //
            // setup.inputChannels.clear();
            // setup.inputChannels.setRange(0, 1, false);
            //
            // setup.outputChannels.clear();
            // setup.outputChannels.setRange(0, 2, true);
            //
            // auto error = deviceManager.setAudioDeviceSetup(setup, false);

            auto error = deviceManager.initialise(0, 2, nullptr, true);

            jassert(error.isEmpty());


            deviceManager.addAudioCallback(&sourcePlayer);
            sourcePlayer.setSource(this);
        }

        void stop()
        {
            sourcePlayer.setSource(nullptr);
            deviceManager.removeAudioCallback(&sourcePlayer);

            // other audio callbacks may still be using the device
            // if (! usingCustomDeviceManager)
                // deviceManager.closeAudioDevice();
        }
    };
}
