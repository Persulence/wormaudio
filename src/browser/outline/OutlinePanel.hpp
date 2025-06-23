#pragma once
#include "outline/OutlineTypes.hpp"
#include "panel/Panel.hpp"

namespace ui
{
    class OutlinePanel : public juce::TreeView
    {
    public:
        OutlinePanel();
        ~OutlinePanel() override;

        void paint(juce::Graphics &g) override;

    private:
        std::unique_ptr<juce::TreeViewItem> root;
    };
}
