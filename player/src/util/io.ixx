module;

#include <memory>

// #include <JuceHeader.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_core/juce_core.h>

export module io;

namespace io
{
    export void readFile(const juce::File& file, juce::AudioFormatManager& formatManager, juce::AudioSampleBuffer& outputBuffer, float maxDuration)
    {
        if (file == juce::File{})
            return;

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
            }
            else
            {
                // handle the error that the file is 2 seconds or longer..
                juce::String message = "file ";
                message << file.getFullPathName() << " longer than " << maxDuration << "s";
                juce::Logger::writeToLog(message);
            }
        }
    }
}
