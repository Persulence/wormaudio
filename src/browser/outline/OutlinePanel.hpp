#pragma once
#include "outline/OutlineTypes.hpp"
#include "panel/Panel.hpp"

namespace ui
{
    class OutlinePanel : public Panel
    {
    public:
        OutlinePanel();

        void resized() override;

        void paint(juce::Graphics &g) override;

    private:
        std::unique_ptr<juce::TreeViewItem> root;
        juce::TreeView treeView;

        OutlineTypeRegistry registry;
    };
}
