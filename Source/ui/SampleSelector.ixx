module;

#include <JuceHeader.h>

#include "../player/SamplePlayer.fwd.h"
#include "../player/SamplePlayer.h"

export module sample_selector;

export class SampleSelector : public juce::Component
{
public:
    explicit SampleSelector(const std::shared_ptr<SamplePlayer> &samplePlayer):
        samplePlayer(samplePlayer)
    {
        addAndMakeVisible(loadFile);
        loadFile.setButtonText("Load file");
        loadFile.onClick = [this]{ loadClicked(); };

        addAndMakeVisible(play);
        play.setButtonText("Play");
        play.onClick = [this]{ playClicked(); };

        addAndMakeVisible(stop);
        stop.setButtonText("Stop");
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
    std::shared_ptr<SamplePlayer> samplePlayer;

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

    }

    void stopClicked()
    {

    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SampleSelector)
};
