module;

#include <JuceHeader.h>

export module sample_selector;

import SamplePlayer;
import transport;

namespace player
{
    export class SampleSelector : public juce::Component
    {
    public:

        explicit SampleSelector(const std::shared_ptr<player::SamplePlayer> &samplePlayer):
            samplePlayer(samplePlayer)
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
        juce::TextButton loadFile;
        juce::TextButton play;
        juce::TextButton stop;
        std::shared_ptr<player::SamplePlayer> samplePlayer;

        std::unique_ptr<juce::FileChooser> chooser;


        void loadClicked()
        {
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
                }
            });
        }

        void playClicked()
        {
            changeState(player::STARTING);
        }

        void stopClicked()
        {
            changeState(STOPPING);
        }

        void changeState(TransportState newState)
        {
            samplePlayer->changeState(newState);
            switch (newState)
            {
                case STARTING:
                {
                    play.setEnabled(false);
                    stop.setEnabled(false);
                }
                case PLAYING:
                {
                    play.setEnabled(false);
                    stop.setEnabled(true);
                }
                case STOPPING:
                {
                    stop.setEnabled(false);
                    play.setEnabled(false);
                }
                case STOPPED:
                {
                    play.setEnabled(true);
                    stop.setEnabled(false);
                }
            }
        }

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SampleSelector)
    };
}