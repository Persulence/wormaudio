#pragma once

#include "editor/Editor.hpp"

#include "panel/Panel.hpp"
#include "util/GuiResources.hpp"

namespace ui
{
    class TransportButton : public juce::Button, player::TransportCallback::Listener
    {
    public:
        using Action = std::function<void(bool)>;

        Action action{[](bool){}};

        explicit TransportButton(const std::string& name, juce::Image icon_):
            Button(name), icon(std::move(icon_))
        {
            listen(editor::Editor::getInstance().transportSignal, [this](auto state)
            {
                setToggleState(state == player::PLAYING, juce::dontSendNotification);
            });
        }

        ~TransportButton() override
        {

        }

        void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
        {
            juce::Colour col;

            if (isToggleable())
                col = getToggleState() ? juce::Colours::lightgrey : juce::Colours::grey;
            else
                col = shouldDrawButtonAsDown ? juce::Colours::lightgrey : juce::Colours::grey;

            g.setColour(col);
            g.fillRect(getLocalBounds());
            g.setColour(juce::Colours::lightgrey);
            g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(0), 5, 2);
            g.drawImage(icon, getLocalBounds().toFloat(), juce::RectanglePlacement::centred, false);
        }

        void clicked() override
        {
            action(isToggleable() ? getToggleState() : isDown());
        }

    private:
        juce::Image icon;
    };

    class TransportPanel : public Panel
    {
        TransportButton playButton{"play", getIcon("icon/play.png")};
        TransportButton stopButton{"stop", getIcon("icon/stop.png")};

        // event::EventInstance::Ptr eventInstance;

    public:
        TransportPanel()
        {
            addAndMakeVisible(playButton);
            playButton.action = [this](bool down){ down ? stop() : play(); };
            playButton.setToggleable(true);
            addAndMakeVisible(stopButton);
            stopButton.action = [this](bool down){ stop(); };
        }

        void play()
        {
            editor::Editor::getInstance().play();
        }

        void stop()
        {
            editor::Editor::getInstance().stop();
        }

        void resized() override;
    };
}