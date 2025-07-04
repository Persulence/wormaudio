#pragma once

#include "command/SimpleCommandTarget.hpp"

namespace ui
{
    class OutlinePanel : public juce::TreeView, public SimpleCommandTarget
    {
    public:
        OutlinePanel();
        ~OutlinePanel() override;

        void paint(juce::Graphics &g) override;

    private:

        std::unique_ptr<juce::TreeViewItem> root;
    };
}
