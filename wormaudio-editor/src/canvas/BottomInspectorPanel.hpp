// Copyright (c) 2025 Persulence
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

        juce::Label helpText;

    public:
        explicit BottomInspectorPanel(CanvasSelectionManager& parent):
            selectionManager(parent)
        {
            onSelect.listen(selectionManager.onSelect, [this]{ updateSelection(); });
            onDeselectAll.listen(selectionManager.onDeselectAll, [this]{ updateSelection(); });

            addAndMakeVisible(helpText);
            helpText.setJustificationType(juce::Justification::centred);
            helpText.setText("No node selected", juce::dontSendNotification);
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
                helpText.setVisible(false);
                repaint();
            }
            else
            {
                configComponent = nullptr;
                helpText.setVisible(true);
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

            helpText.setBounds(getLocalBounds());
        }
    };
}