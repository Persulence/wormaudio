module;

#include <variant>
#include <memory>

export module Element;

import ElementInstance;
import AudioContext;

namespace element
{
    // Elements are shared resources
    export class Element
    {
    public:
        [[nodiscard]] virtual ElementInstancePtr createInstance(player::AudioContext) const = 0;

        virtual ~Element() = default;
    };

    export class RandomElement : public Element
    {

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