// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    class Panel : public juce::Component
    {
    protected:
        juce::Colour fg{juce::Colours::lightgrey};
        juce::Colour bg{juce::Colours::grey};

        /// For maintaining ownership of components that don't need to be referenced after construction
        std::vector<std::unique_ptr<Component>> nonameOwned;

    public:
        static void paintBorder(juce::Graphics& g, juce::Rectangle<int> bounds, float borderWidth)
        {
            g.setColour(juce::Colours::lightgrey);
            g.drawRoundedRectangle(bounds.toFloat().reduced(borderWidth / 2, borderWidth / 2), 5, borderWidth);
        }

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Panel)

        Panel() = default;

        void paint(juce::Graphics &g) override;
    protected:

        void paintBackground(juce::Graphics &g) const;
        void paintBorder(juce::Graphics &g) const;

        // template <typename T>
        // Component* withNoname(Component&& noname, T& t)
        // {
        //     noname.addAndMakeVisible(t);
        //     nonameOwned.push_back(std::move(noname));
        //     return &noname;
        // }

        template <typename T>
        Component* withNoname(Component& c)
        {
            auto& noname = nonameOwned.emplace_back(std::make_unique<T>(c));
            return noname.get();
        }
    };
}
