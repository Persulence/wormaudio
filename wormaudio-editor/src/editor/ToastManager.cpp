
// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "ToastManager.hpp"

#include "panel/Panel.hpp"
#include "UiMainComponent.hpp"
#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    class ToastComponent : public Panel
    {
    public:
        ToastComponent(std::string message_, ToastManager::MessageType type_):
            message(std::move(message_)), type(type_)
        {
            juce::Timer::callAfterDelay(5000, [this]{ done(); });

            addAndMakeVisible(label);
            label.setText(message, juce::dontSendNotification);

            int width = label.getFont().getStringWidth(message);

            // Some jank
            std::stringstream ss;
            ss << message;
            auto lines = std::count_if(std::istreambuf_iterator{ss}, {}, [](char c) { return c == '\n'; });

            // ???
            if (lines == 0)
                lines = 1;

            lines++;

            label.setBounds(0, 0, width + 10, static_cast<int>(lines * label.getFont().getHeight()));
            setBounds(label.getBoundsInParent());

            label.setFont(label.getFont().withStyle(juce::Font::FontStyleFlags::bold));

            switch (type)
            {
                case ToastManager::INFO:
                    label.setColour(label.textColourId, juce::Colours::white);
                    break;
                case ToastManager::WARNING:
                    label.setColour(label.textColourId, juce::Colours::orange);
                    break;
                case ToastManager::ERROR:
                    label.setColour(label.textColourId, juce::Colours::red);
                    break;
            }
        }

        void paint(juce::Graphics &g) override
        {
            paintBackground(g);
            Panel::paintBorder(g, getLocalBounds(), 1);
        }

        void done()
        {
            UiMainComponent::getInstance().removeToast(this);
        }

        juce::Label label;
        std::string message;
        ToastManager::MessageType type;
    };

    void ToastManager::addMessage(std::string message, MessageType type)
    {
        std::unique_ptr<juce::Component> toast = std::make_unique<ToastComponent>(message, type);
        UiMainComponent::getInstance().addToast(std::move(toast));
    }
}
