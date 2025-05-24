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

        void select(const std::shared_ptr<CanvasSelectionTarget> &target)
        {
            if (!current.expired())
            {
                if (auto shared = current.lock(); shared != nullptr && shared != target)
                {
                    shared->onDeselect();
                }
            }

            if (target)
                target->onSelect();
            current = target;
            onSelect();
        }

    protected:
        virtual void onSelect() = 0;
    };
}
