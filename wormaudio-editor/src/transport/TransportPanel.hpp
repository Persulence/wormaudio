// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include "command/Commands.hpp"
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
            editor::getInstance().play();
        }

        void stop()
        {
            editor::getInstance().stop();
        }

        void resized() override;
    };
}