#pragma once

#include "juce_gui_basics/juce_gui_basics.h"

#include "util/Data.hpp"
#include "util/component/MyLabel.hpp"

namespace ui
{
    class OutlineItemComponent : public juce::Component
    {
    public:
        OutlineItemComponent(juce::TreeViewItem* item_, const std::string &icon, bool editable = true);
        explicit OutlineItemComponent(juce::TreeViewItem* item_);

        void paint(juce::Graphics &g) override;
        void resized() override;

        void rename();

    public:
        MyLabel<std::string> label;

        juce::Image icon;
        juce::TreeViewItem *item;

    protected:
        bool dragging{false};

    private:
        juce::Rectangle<int> iconBounds;
    };
}
