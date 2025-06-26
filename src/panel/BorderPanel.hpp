#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "panel/Panel.hpp"

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
            Panel::paintBorder(g, getLocalBounds(), borderWidth);
            // g.drawRect(getLocalBounds(), borderWidth);
        }
    };
}
