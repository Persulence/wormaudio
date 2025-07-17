// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "../panel/Panel.hpp"
#include "CanvasSelectionManager.hpp"

namespace ui
{
    class BottomInspectorPanel : public Panel
    {
        CanvasSelectionManager& selectionManager;

        std::mutex configMutex;
        std::shared_ptr<Component> configComponent;

        CanvasSelectionManager::ChangeCallback::Listener onSelect;
        CanvasSelectionManager::ChangeCallback::Listener onDeselectAll;

    public:
        explicit BottomInspectorPanel(CanvasSelectionManager& parent):
            selectionManager(parent)
        {
            onSelect.listen(selectionManager.onSelect, [this]{ updateSelection(); });
            onDeselectAll.listen(selectionManager.onDeselectAll, [this]{ updateSelection(); });
        }

        void updateSelection()
        {
            std::lock_guard lock{configMutex};
            if (configComponent)
            {
                removeChildComponent(configComponent.get());
            }

            if (const auto shared = selectionManager.getCurrent().lock(); shared != nullptr)
            {
                configComponent = shared->createConfig();
                addAndMakeVisible(configComponent.get());
                configComponent->setBounds(getLocalBounds());
                repaint();
            }
            else
            {
                configComponent = nullptr;
            }
        }

        void paint(juce::Graphics &g) override
        {
            paintBackground(g);
            // paintBorder(g);
        }

        void resized() override
        {
            if (configComponent != nullptr)
            {
                configComponent->setBounds(getLocalBounds());
            }
        }
    };
}