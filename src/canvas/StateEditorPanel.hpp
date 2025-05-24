#pragma once

#include "../panel/Panel.hpp"
#include "CanvasSelectionManager.hpp"

namespace ui
{
    class StateEditorPanel : public Panel
    {
        CanvasSelectionManager& selectionManager;
        std::shared_ptr<Component> configComponent;

    public:
        explicit StateEditorPanel(CanvasSelectionManager& parent):
            selectionManager(parent)
        {
        }

        void updateSelection(std::weak_ptr<CanvasSelectionTarget> curent)
        {
            if (!selectionManager.getCurrent().expired())
            {
                auto shared = selectionManager.getCurrent().lock();
                configComponent = shared->createConfig();
                addAndMakeVisible(configComponent.get());
                configComponent->setBounds(getLocalBounds());
                repaint();
            }
        }

        void paint(juce::Graphics &g) override
        {
            paintBackground(g);
            paintBorder(g);
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