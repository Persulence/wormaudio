#pragma once

#include <runtime/Runtime.hpp>
#include <editor/Editor.hpp>

#include "panel/Panel.hpp"
#include "util/GuiResources.hpp"

namespace ui
{
    class TransportButton : public juce::Button
    {
    public:
        using Action = std::function<void(bool)>;

        Action action{[](bool){}};

        explicit TransportButton(const std::string& name, juce::Image icon_):
            Button(name), icon(std::move(icon_))
        {
        }

        void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
        {
            auto col = shouldDrawButtonAsDown ? juce::Colours::lightgrey : juce::Colours::grey;
            g.setColour(col);
            g.fillRect(getLocalBounds());
            g.setColour(juce::Colours::lightgrey);
            g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(0), 5, 2);
            g.drawImage(icon, getLocalBounds().toFloat(), juce::RectanglePlacement::centred, false);
        }

        void clicked() override
        {
            // action(isDown());
        }

    private:
        juce::Image icon;
    };

    class TransportPanel : public Panel
    {
        TransportButton playButton{"play", getIcon("icon/play.png")};
        TransportButton stopButton{"stop", getIcon("icon/stop.png")};

        event::EventInstance::Ptr eventInstance;

    public:
        TransportPanel()
        {
            addAndMakeVisible(playButton);
            playButton.action = [this](bool down){ down ? play() : stop(); };
            playButton.setToggleable(true);
            addAndMakeVisible(stopButton);
            stopButton.action = [this](bool down){ stop(); };
        }

        void play()
        {
            // eventInstance = editor::Editor::getInstance().getEvent()->instantiate();
            auto& editor = editor::Editor::getInstance();
            eventInstance = editor.getRuntime().instantiate(editor::Editor::getInstance().getEvent());
        }

        void stop()
        {
            auto& editor = editor::Editor::getInstance();
            editor.getRuntime().clearInstances();
        }

        void resized() override;
    };
}