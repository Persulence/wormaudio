#include "SamplePlayer.h"


SamplePlayer::SamplePlayer()
{
    formatManager.registerBasicFormats();
    transportSource.addChangeListener(this);
}

void SamplePlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill)
{
    if (readerSource.get() == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }

    transportSource.getNextAudioBlock(bufferToFill);
}

void SamplePlayer::changeState(TransportState state)
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
    }
}

void SamplePlayer::setFile(juce::File &&file)
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

void SamplePlayer::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    if (source == &transportSource)
    {
        if (transportSource.isPlaying())
            changeState(PLAYING);
        else
            changeState(STOPPED);
    }
}
