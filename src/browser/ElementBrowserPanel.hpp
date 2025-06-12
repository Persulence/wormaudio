#pragma once

#include "ElementListPanel.hpp"
#include "../panel/Panel.hpp"

namespace ui
{
    class ElementBrowserPanel : public Panel
    {
    public:
        ElementBrowserPanel();
        void paint(juce::Graphics &g) override;
        void resized() override;

    private:
        ElementListPanel listPanel;
    };
}

