
// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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

            label.setBounds(0, 0, width + 10, lines * label.getFont().getHeight());
            setBounds(label.getBoundsInParent());
            // setBoundsToFit(label.getBoundsInParent(), juce::Justification::centred, );
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
