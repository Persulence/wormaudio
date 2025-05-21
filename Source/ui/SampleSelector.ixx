module;

#include <JuceHeader.h>

#include <utility>

export module sample_selector;

import SamplePlayer;
import transport;

namespace player
{
    export class SampleSelector : public juce::Component
    {
    public:
        using Shutdown = std::function<void()>;
        using Restart = std::function<void(int inputChannels, int outputChannels)>;

    private:
        Shutdown shutdown;
        Restart restart;

        juce::TextButton loadFile;
        juce::TextButton play;
        juce::TextButton stop;
        std::shared_ptr<SamplePlayer> samplePlayer;

        std::unique_ptr<juce::FileChooser> chooser;

    public:
        explicit SampleSelector(const std::shared_ptr<SamplePlayer> &samplePlayer, Shutdown shutdown_, Restart restart_):
            samplePlayer(samplePlayer),
            shutdown(std::move(shutdown_)),
            restart(std::move(restart_))
        {
            addAndMakeVisible(loadFile);
            loadFile.setButtonText("Load file");
            loadFile.onClick = [this]{ loadClicked(); };

            addAndMakeVisible(play);
            play.setButtonText("Play");
            play.setColour(juce::TextButton::buttonColourId, juce::Colours::teal);
            play.onClick = [this]{ playClicked(); };

            addAndMakeVisible(stop);
            stop.setButtonText("Stop");
            stop.setColour(juce::TextButton::buttonColourId, juce::Colours::indianred);
            stop.onClick = [this] { stopClicked(); };

            samplePlayer->setTransportCallback([this](auto state) { changeState(state); });
        }

        void resized() override
        {
            int bh = 20;
            auto rect = getLocalBounds();
            loadFile.setBounds(rect.removeFromTop(bh));
            play.setBounds(rect.removeFromTop(bh));
            stop.setBounds(rect.removeFromTop(bh));
        }

        ~SampleSelector() override = default;

    private:

        void loadClicked()
        {
            shutdown();
            changeState(STOPPED);
            chooser = std::make_unique<juce::FileChooser> ("Select a Wave file to play...",
            juce::File {},
            "*.wav");
            auto chooserFlags = juce::FileBrowserComponent::openMode
                                | juce::FileBrowserComponent::canSelectFiles;
            chooser->launchAsync (chooserFlags, [this] (const juce::FileChooser& fc) // [8]
            {
                auto file = fc.getResult();
                if (file != juce::File {})
                {
                    samplePlayer->setFile(std::move(file));
                    restart(0, 2);
                }
            });
        }

        void playClicked()
        {
            changeState(STARTING);
        }

        void stopClicked()
        {
            changeState(STOPPING);
        }

        void changeState(TransportState newState)
        {
            switch (newState)
            {
                case STARTING:
                {
                    play.setEnabled(false);
                    stop.setEnabled(false);
                    break;
                }
                case PLAYING:
                {
                    play.setEnabled(false);
                    stop.setEnabled(true);
                    break;
                }
                case STOPPING:
                {
                    stop.setEnabled(false);
                    play.setEnabled(false);
                    break;
                }
                case STOPPED:
                {
                    play.setEnabled(true);
                    stop.setEnabled(false);
                    break;
                }
            }

            samplePlayer->changeState(newState);
        }

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SampleSelector)
    };
}