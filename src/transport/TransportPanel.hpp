#pragma once

#include "panel/Panel.hpp"
#include "util/GuiResources.hpp"

namespace ui
{
    class TransportButton : public juce::Button
    {
        juce::Image icon;

    public:
        explicit TransportButton(const std::string& name, juce::Image icon_):
            Button(name), icon(std::move(icon_))
        {

        }

        void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
        {
            // float width =
            // g.setColour(juce::Colours::black);
            // g.fillRect(getLocalBounds());
            g.setColour(juce::Colours::lightgrey);
            g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(0), 5, 2);
            g.drawImage(icon, getLocalBounds().toFloat(), juce::RectanglePlacement::centred, false);
        }

        void clicked() override
        {
        }

    };

    class TransportPanel : public Panel
    {
        TransportButton playButton{"play", getIcon("icon/play.png")};
        TransportButton stopButton{"stop", getIcon("icon/stop.png")};

    public:
        TransportPanel()
        {
            addAndMakeVisible(playButton);
            addAndMakeVisible(stopButton);
        }

        void play();

        void stop();

        void resized() override;
    };
}