#pragma once
#include "panel/Panel.hpp"

namespace ui
{
    class ParameterPanel : public Panel
    {
    public:
        void paint(juce::Graphics &g) override;
    };
}
