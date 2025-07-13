// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "canvas/InspectorSelectionManager.hpp"

#include "panel/Panel.hpp"

namespace ui
{
    class RightInspectorPanel : public Panel
    {
        InspectorSelectionManager::ChangeCallback::Listener onSelect;
        InspectorSelectionManager::ChangeCallback::Listener onDeselectAll;

        std::mutex configMutex;
        std::shared_ptr<Component> configComponent;

    public:
        explicit RightInspectorPanel(InspectorSelectionManager &manager):
            manager(manager)
        {
            onSelect.listen(manager.onSelect, [this]{ updateSelection(); });
            onDeselectAll.listen(manager.onDeselectAll, [this]{ updateSelection(); });
        }

        void updateSelection()
        {
            std::lock_guard lock{configMutex};
            if (configComponent)
            {
                removeChildComponent(configComponent.get());
            }

            if (const auto shared = manager.getCurrent().lock(); shared != nullptr)
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
        }

        void resized() override
        {
            if (configComponent != nullptr)
            {
                configComponent->setBounds(getLocalBounds());
            }
        }

    private:
        InspectorSelectionManager& manager;
    };
}
