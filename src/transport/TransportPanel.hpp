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
        using Action = std::function<void()>;

        Action action{[]{}};

        explicit TransportButton(const std::string& name, juce::Image icon_):
            Button(name), icon(std::move(icon_))
        {

        }

        void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
        {
            auto col = shouldDrawButtonAsHighlighted ? juce::Colours::lightgrey : juce::Colours::grey;
            g.setColour(col);
            g.fillRect(getLocalBounds());
            g.setColour(juce::Colours::lightgrey);
            g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(0), 5, 2);
            g.drawImage(icon, getLocalBounds().toFloat(), juce::RectanglePlacement::centred, false);
        }

        void clicked() override
        {
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
            playButton.action = [this]{ play(); };
            addAndMakeVisible(stopButton);
            stopButton.action = [this]{stop(); };
        }

        void play()
        {
            // eventInstance = editor::Editor::getInstance().getEvent()->instantiate();
            auto& editor = editor::Editor::getInstance();
            eventInstance = editor.getRuntime().instantiate(editor::Editor::getInstance().getEvent());
        }

        void stop()
        {

        }

        void resized() override;
    };
}