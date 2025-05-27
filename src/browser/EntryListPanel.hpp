#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "../panel/Panel.hpp"

namespace ui
{
    using EntryListCallback = std::function<void(int items)>;

    template <typename Entry>
    class EntryListPanel : public Panel
    {
    public:
        EntryListCallback callback = [](int){};

        void paint(juce::Graphics &g) override
        {
            paintBackground(g);
        }

        int getExpectedHeight() const
        {
            return expectedHeight;
        }

    protected:
        juce::Font font{juce::Font{juce::FontOptions{}}};
        std::vector<std::shared_ptr<Entry>> fileWidgets;
        int entryH{30};
        int expectedHeight = 30;

        double scrollFraction{0};

        virtual int getEntryHeight()
        {
            return entryH;
        }

    };

}
