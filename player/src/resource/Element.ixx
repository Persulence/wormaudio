module;

#include <variant>
#include <memory>

#include "../automation/AutomationRegistry.hpp"
#include "../util/class_util.h"
#include "automation/AutomationInstance.hpp"

export module element;

import ElementInstance;
import AudioContext;

export import :ElementInstanceContext;

namespace element
{
    // Elements are shared resources
    export class Element : public automation::PropertyProvider
    {
    public:
        Element() = default;
        JUCE_DECLARE_NON_COPYABLE(Element)

        [[nodiscard]] virtual ElementInstancePtr createInstance(player::AudioContext, automation::AutomationInstance& automation) = 0;
        virtual std::string getName() = 0;

        // virtual void regAutomation(automation::AutomationRegistry& registry) const { }

        ~Element() override = default;
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