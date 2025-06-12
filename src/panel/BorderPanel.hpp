#pragma once

#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    template<typename Child> requires std::convertible_to<Child&, juce::Component&>
    class BorderPanel : public juce::Component
    {
        float borderWidth{1};

    public:
        Child child;

        template <typename... Args>
        explicit BorderPanel(Args&&... args):
            child(Child{std::forward<Args>(args)...})
        {
            addAndMakeVisible(child);
        }

        BorderPanel():
            child(Child{})
        {
            addAndMakeVisible(child);
        }

        Child* operator->() noexcept
        {
            return &child;
        }

        void resized() override
        {
            auto bounds = getLocalBounds();
            bounds.reduce(borderWidth, borderWidth);
            child.setBounds(bounds);
        }

        void paint(juce::Graphics &g) override
        {
            g.setColour(juce::Colours::lightgrey);
            g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(borderWidth / 2, borderWidth / 2), 5, borderWidth);
            // g.drawRect(getLocalBounds(), borderWidth);
        }
    };
}
