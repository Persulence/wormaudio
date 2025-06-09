#pragma once

#include "../panel/Panel.hpp"
#include "CanvasSelectionManager.hpp"

namespace ui
{
    class BottomInspectorPanel : public Panel
    {
        CanvasSelectionManager& selectionManager;
        std::shared_ptr<Component> configComponent;

    public:
        explicit BottomInspectorPanel(CanvasSelectionManager& parent):
            selectionManager(parent)
        {
        }

        void updateSelection()
        {
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