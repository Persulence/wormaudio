#pragma once
#include "../panel/Panel.hpp"

namespace ui
{
    class ElementBrowserPanel : public Panel
    {
        void paint(juce::Graphics &g) override;
    };
}

