#pragma once

#include <panel/Panel.hpp>

namespace ui
{
    class StateNodeWidget;
}

namespace ui
{
    class StatePropertyPanel : public Panel
    {
    private:
        std::weak_ptr<StateNodeWidget> parent;

    public:
        StatePropertyPanel(std::weak_ptr<StateNodeWidget> parent_):
            parent(std::move(parent_))
        {
        }

        void paint(juce::Graphics &g) override;
    };
}
