// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
