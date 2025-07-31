// Copyright (c)  2025 Persulence
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

#include <any>

#include "juce_gui_basics/juce_gui_basics.h"
#include "resource/SharedResource.hpp"

namespace ui
{
    class OutlineTypeRegistry
    {
        class EmptyResult : public juce::TreeViewItem
        {
        public:
            bool mightContainSubItems() override
            {
                return false;
            }

            void paintItem(juce::Graphics &g, int width, int height) override
            {
                g.setColour(juce::Colours::red);
                g.fillRect(0, 0, width, height);
            }
        };

    public:
        using Result = std::unique_ptr<juce::TreeViewItem>;

        template <resource::IsResource T>
        using FactoryT = std::function<Result(resource::Handle<T>)>;
        using Factory = std::function<Result(std::any)>;

        static OutlineTypeRegistry& getInstance()
        {
            static OutlineTypeRegistry instance;
            return instance;
        }

        Result get(resource::ResourceHandle handle) const
        {
            auto& object = *handle;
            if (const auto it = map.find(std::type_index{typeid(object)}); it != map.end())
            {
                return it->second(handle);
            }
            else
            {
                return std::make_unique<EmptyResult>();
            }
        }

        template <resource::IsResource T>
        void reg(FactoryT<T> factory)
        {
            map[std::type_index{typeid(T)}] = wrapFactory(factory);
        }

        /// Erases the input type of FactoryT
        template <resource::IsResource T>
        static std::function<Result(std::any)> wrapFactory(FactoryT<T> factory)
        {
            return [factory](const std::any &any)
            {
                // Convert the any to a ResourceHande and then to a Handle<T>, then apply the factory
                return factory(
                    std::dynamic_pointer_cast<T>(
                        std::any_cast<resource::ResourceHandle>(any)));
            };
        }

    private:
        JUCE_DECLARE_NON_COPYABLE(OutlineTypeRegistry)

        std::unordered_map<std::type_index, Factory> map;

        OutlineTypeRegistry()
        {
            regDefaults();
        }

        void regDefaults();
    };

}
