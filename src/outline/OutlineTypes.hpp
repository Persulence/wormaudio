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
            if (const auto it = map.find(std::type_index{typeid(*handle)}); it != map.end())
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
