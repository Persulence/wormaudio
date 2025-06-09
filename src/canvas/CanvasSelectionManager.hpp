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
        virtual void onSelect() {};

        /// Executed when the selection has changed to another object.
        virtual void onDeselect() {};
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

        template <class T>
        std::shared_ptr<T> getCurrent()
        {
            std::shared_ptr<CanvasSelectionTarget> shared = current.lock();

            return std::dynamic_pointer_cast<T>(shared);
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

        void deselectAll()
        {
            if (auto shared = current.lock())
            {
                shared->onDeselect();
            }

            current = std::weak_ptr<CanvasSelectionTarget>();

            onDeselectAll();
        }

    protected:
        virtual void onSelect() = 0;
        virtual void onDeselectAll() = 0;
    };
}
