#pragma once

#include <memory>

#include "signal/Signal.hpp"

namespace juce
{
    class Component;
}

namespace ui
{
    class SelectionTarget
    {
    public:
        virtual ~SelectionTarget() = default;

        virtual std::shared_ptr<juce::Component> createConfig() = 0;

        /// Executed when the selection manager has confirmed selection of this object.
        virtual void onSelect() {};

        /// Executed when the selection has changed to another object.
        virtual void onDeselect() {};
    };

    class SelectionManager
    {
    protected:
        std::weak_ptr<SelectionTarget> current;

    public:
        using ChangeCallback = signal_event::Callback<>;
        ChangeCallback::Signal onSelect;
        ChangeCallback::Signal onDeselectAll;

        virtual ~SelectionManager() = default;

        std::weak_ptr<SelectionTarget> getCurrent()
        {
            return current;
        }

        template <class T>
        std::shared_ptr<T> getCurrent()
        {
            std::shared_ptr<SelectionTarget> shared = current.lock();

            return std::dynamic_pointer_cast<T>(shared);
        }

        void select(const std::shared_ptr<SelectionTarget> &target)
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
            onSelect.emit();
        }

        void deselectAll()
        {
            if (auto shared = current.lock())
            {
                shared->onDeselect();
            }

            current = std::weak_ptr<SelectionTarget>();

            onDeselectAll.emit();
        }

    protected:
        // virtual void onSelect() = 0;
        // virtual void onDeselectAll() = 0;

        // Using callbacks instead of virtual functions as inheritance of multiple subclasses must be possible.
        // It's the 'cleanest' solution.
        // It's because of JUCE. Not my fault.
        // std::function<void()> onSelect{[]{}};
        // std::function<void()> onDeselectAll{[]{}};
    };
}
