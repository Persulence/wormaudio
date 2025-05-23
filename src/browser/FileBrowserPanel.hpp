#pragma once
#include "../Panel.hpp"

namespace ui
{
    class FileBrowserPanel : public ui::Panel
    {
        void paint(juce::Graphics &g) override;
    };
}

