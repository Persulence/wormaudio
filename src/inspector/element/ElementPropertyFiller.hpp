#pragma once
#include "event/ElementHandle.hpp"
#include "property/PropertyFiller.hpp"

namespace ui
{
    class ElementPropertyFiller : public PropertyFiller
    {
    public:
        explicit ElementPropertyFiller(event::ElementHandle handle_);
        void initProperties() override;

    private:
        event::ElementHandle handle;
    };
}
