// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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

    class SimpleSelectionTarget : public SelectionTarget
    {
    public:
        static std::shared_ptr<SimpleSelectionTarget> of(std::unique_ptr<juce::Component> config)
        {
            return std::make_unique<SimpleSelectionTarget>(std::move(config));
        }

        explicit SimpleSelectionTarget(std::unique_ptr<juce::Component> config_):
            config(std::move(config_)) { }

        std::shared_ptr<juce::Component> createConfig() override
        {
            return config;
        }

    private:
        std::shared_ptr<juce::Component> config;
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
