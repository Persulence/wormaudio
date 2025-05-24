#pragma once

#include <iostream>
#include <memory>

namespace juce {
    class Component;
}

namespace ui
{
    class CanvasSelectionTarget
    {
    public:
        virtual ~CanvasSelectionTarget() = default;

        virtual std::unique_ptr<juce::Component> createConfig() = 0;
    };

    // To be accessed via Component::findParentOfClass. Requires janky multiple inheritance.
    class CanvasSelectionManager
    {
    protected:
        std::weak_ptr<CanvasSelectionTarget> current;

    public:
        virtual ~CanvasSelectionManager() = default;

        std::weak_ptr<CanvasSelectionTarget> getCurrent()
        {
            return current;
        }

        void select(std::shared_ptr<CanvasSelectionTarget> target)
        {
            current = target;
            onSelect();
        }

    protected:
        virtual void onSelect() = 0;
    };
}
