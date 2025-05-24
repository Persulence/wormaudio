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

        virtual std::shared_ptr<juce::Component> createConfig() = 0;

        /// Executed when the selection manager has confirmed selection of this object.
        virtual void onSelect() = 0;

        /// Executed when the selection has changed to another object.
        virtual void onDeselect() = 0;
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
            if (!current.expired())
            {
                if (auto shared = current.lock(); shared != target)
                {
                    shared->onDeselect();
                }
            }

            target->onSelect();
            current = target;
            onSelect(current);
        }

    protected:
        virtual void onSelect(std::weak_ptr<CanvasSelectionTarget> current) = 0;
    };
}
