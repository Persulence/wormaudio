// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include <JuceHeader.h>

#include "resource/ElementInstance.hpp"

class Track : public juce::AudioSource
{
        std::vector<element::ElementInstancePtr> active;

public:
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
    {

    }

    void releaseResources() override
    {
        active.clear();
    }

    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override
    {
        for (const auto& instance : active)
        {
            instance->getNextAudioBlock(bufferToFill);
        }
    }
};
