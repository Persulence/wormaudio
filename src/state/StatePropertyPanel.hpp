#pragma once

#include <browser/FileDragSource.hpp>
#include <canvas/StateNodeWidget.hpp>
#include <panel/Panel.hpp>

#include "ElementRegion.hpp"

#include "Runtime.hpp"

import ElementTypes;
import Resource;

namespace ui
{
    class StateNodeWidget;
}

namespace ui
{
    class StatePropertyPanel : public Panel, public juce::DragAndDropTarget
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

        bool isInterestedInDragSource(const SourceDetails &dragSourceDetails) override
        {
            return dynamic_cast<FileDragSource*>(dragSourceDetails.sourceComponent.get());
        }

        void itemDropped(const SourceDetails &dragSourceDetails) override
        {
            if (auto source = dynamic_cast<FileDragSource*>(dragSourceDetails.sourceComponent.get()))
            {
                if (const auto shared = parent.lock())
                {
                    // TODO create element in event and add appropriate widget
                    // auto resource = std::make_shared<resource::Resource>(runtime::getResourceLoader(), source->getFile());
                    auto resource = runtime::createResource(source->getFile());
                    shared->getState()->insertElement(std::make_shared<element::ClipElement>(resource));
                    update();
                    resized();
                    repaint();
                }
            }
        }
    };
}
