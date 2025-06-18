#pragma once

#include <any>

#include "juce_gui_basics/juce_gui_basics.h"
#include "resource/SharedResource.hpp"

namespace ui
{
    class OutlineTypeRegistry
    {
    public:
        using Result = std::unique_ptr<juce::TreeViewItem>;
        template <resource::IsResource T>
        using FactoryT = std::function<Result(resource::Handle<T>)>;
        using Factory = std::function<Result(std::any)>;

        Result get(resource::ResourceHandle handle) const
        {
            return map.at(std::type_index{typeid(*handle)})(handle);
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

        // Convertible to Factory
        // struct Entry
        // {
        //     std::function<Result(std::any)> mapping;
        //
        //     template <resource::IsResource T>
        //     explicit Entry(auto mappingIn)
        //     {
        //         mapping = [mappingIn](auto& a)
        //         {
        //             return mappingIn(dynamic_cast<resource::Handle<T>>(a));
        //         };
        //     }
        //
        //     Result operator()(const std::any &obj) const
        //     {
        //         return mapping(obj);
        //     }
        // };

    private:
        std::unordered_map<std::type_index, Factory> map;
    };

    void regDefaults(OutlineTypeRegistry& registry);
}
