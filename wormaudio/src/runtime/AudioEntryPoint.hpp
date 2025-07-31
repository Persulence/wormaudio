// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
