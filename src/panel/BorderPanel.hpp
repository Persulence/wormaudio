#pragma once

#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    template<typename Child> requires std::convertible_to<Child&, juce::Component&>
    class BorderPanel : public juce::Component
    {
        float borderWidth{2};

    public:
        // using ChildVariant = std::variant<Child, Child*>;
        Child child;

        // BorderPanel(Child& child_):
        //     child(&child_)
        // {
        //     addAndMakeVisible(child_);
        // }

        template <typename... Args>
        explicit BorderPanel(Args&... args):
            child(Child{args...})
        {
            addAndMakeVisible(child);
        }

        BorderPanel():
            child(Child{})
        {
            addAndMakeVisible(child);
        }

        // template <class... Ts>
        // struct Visitor : Ts... { using Ts::operator()...; };

        // struct Visitor2
        // {
        //     const Child* operator()(const Child& c)
        //     {
        //         return &c;
        //     }
        //
        //     const Child* operator()(const Child* c)
        //     {
        //         return c;
        //     }
        // };

        Child* operator->() noexcept
        {
            // return std::visit(Visitor{
            //     [](const Child& c){ return &c; },
            //     [](const Child* c){ return c; }
            // }, child);

            // return std::visit(Visitor{}, child);

            return &child;
        }

        void resized() override
        {
            auto bounds = getLocalBounds();
            bounds.reduce(static_cast<float>(borderWidth), static_cast<float>(borderWidth));
            child.setBounds(bounds);
        }

        void paint(juce::Graphics &g) override
        {
            g.setColour(juce::Colours::lightgrey);
            g.drawRoundedRectangle(getLocalBounds().toFloat(), 5, borderWidth);
//            g.drawRect(getLocalBounds(), static_cast<float>(borderWidth));
        }
    };
}
