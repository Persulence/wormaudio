// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include <memory>

// #include <JuceHeader.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_core/juce_core.h>

namespace io
{
    inline bool readFile(const juce::File& file, juce::AudioFormatManager& formatManager, juce::AudioSampleBuffer& outputBuffer, float maxDuration)
    {
        if (file == juce::File{})
            return false;

        const std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));

        if (reader != nullptr)
        {
            double duration = static_cast<double>(reader->lengthInSamples) / reader->sampleRate;
            if (duration < maxDuration)
            {
                outputBuffer.setSize(static_cast<int>(reader->numChannels), static_cast<int>(reader->lengthInSamples));
                reader->read(
                        &outputBuffer,
                        0,
                        static_cast<int>(reader->lengthInSamples),
                        0,
                        true,
                        true);

                // setAudioChannels(0, reader->numChannels);

                return true;
            }
            else
            {
                juce::String message = "file ";
                message << file.getFullPathName() << " longer than " << maxDuration << "s";
                juce::Logger::writeToLog(message);

                return false;
            }
        }

        return false;
    }
}
