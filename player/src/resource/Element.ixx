module;

#include <memory>

#include "SharedResource.hpp"
#include "automation/instance/AutomationRegistryInstance.hpp"
#include "util/AudioContext.hpp"

export module element;

import ElementInstance;

export import :ElementInstanceContext;

namespace element
{
    // Elements are shared resources
    export class Element : public resource::SharedResource, public automation::PropertyProvider
    {
    public:
        automation::Property volume{automation::createProperty("volume", 0, automation::Unit::DBFS)};

        Element() = default;

        [[nodiscard]] virtual ElementInstancePtr createInstance(player::AudioContext, automation::AutomationRegistryInstance& automation) = 0;
        virtual std::string getName() = 0;

        ~Element() override = default;
        JUCE_DECLARE_NON_COPYABLE(Element)
    };

    export class RandomElement : public Element
    {
        std::string getName() override { return "random"; }
    };

//    export template <class T> requires (std::convertible_to<Element&, T&>)
//    ElementInstance createInstance(const T& element)
//    {
//
//    }
//
//    void ooer()
//    {
//        Element element1;
//        createInstance<Element>(element1);
//    }
}