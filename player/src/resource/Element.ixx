module;

#include <variant>
#include <memory>

#include "../util/class_util.h"

export module element;

import ElementInstance;
import AudioContext;

export import :ElementInstanceContext;

namespace element
{
    // Elements are shared resources
    export class Element
    {
    public:
        Element() = default;
        JUCE_DECLARE_NON_COPYABLE(Element)

        [[nodiscard]] virtual ElementInstancePtr createInstance(player::AudioContext) const = 0;

        virtual std::string getName() = 0;

        virtual ~Element() = default;
    };

    export class RandomElement : public Element
    {
        std::string getName() override { return "random"; };
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