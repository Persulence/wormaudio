#pragma once

#include <canvas/StateNodeWidget.hpp>
#include <panel/Panel.hpp>

#include "ElementRegion.hpp"

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
        std::vector<std::shared_ptr<ElementRegion>> elements;

    public:
        StatePropertyPanel(std::weak_ptr<StateNodeWidget> parent_):
            parent(std::move(parent_))
        {
            update();
        }

        // Implementation for faster iteration
        void paint(juce::Graphics &g) override;
        void resized() override;
        void mouseDown(const juce::MouseEvent &event) override;

        void update()
        {
            elements.clear();
            removeAllChildren();

            if (const auto shared = parent.lock())
            {
                for (auto& element : shared->getState()->elements())
                {
                    auto& widget = elements.emplace_back(std::make_shared<ElementRegion>(element.value));
                    addAndMakeVisible(*widget);
                }
            }
        }


    };
}
