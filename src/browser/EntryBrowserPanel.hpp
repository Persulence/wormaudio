#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "../panel/Panel.hpp"

namespace ui
{
    template <typename Entry>
    class EntryBrowserPanel : public Panel
    {
    public:
        void paint(juce::Graphics &g) override
        {
            paintBackground(g);
        }

    protected:
        juce::Font font{juce::Font{juce::FontOptions{}}};
        std::vector<std::shared_ptr<Entry>> fileWidgets;
        int entryH{30};

        virtual int getEntryHeight(Entry& entry) { return entryH; };

    };

}
