#include "ElementPropertyFiller.hpp"

#include "panel/MyPropertyPanel.hpp"

import ElementTypes;

namespace ui
{
    using namespace element;

    class ClipImpl : public PropertyFiller
    {
        ClipElement& element;

    public:
        explicit ClipImpl(ClipElement &element) :
            element(element)
        {
            ClipImpl::initProperties();
        }

        void initProperties() override
        {
            add(std::make_shared<BoolPropertyWidget>("Loop", element.loop));
        }
    };

    ElementPropertyFiller::ElementPropertyFiller(event::ElementHandle handle_):
        handle(std::move(handle_))
    {
        ElementPropertyFiller::initProperties();
    }

    void ElementPropertyFiller::initProperties()
    {
        // Urgh
        if (typeid(*handle.ptr) == typeid(ClipElement))
        {
            add(std::make_shared<ClipImpl>(dynamic_cast<ClipElement&>(*handle.ptr)));
        }
    }
}
