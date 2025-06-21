#pragma once
#include "event/ElementHandle.hpp"
#include "property/PropertyFiller.hpp"

namespace ui
{
    class ElementInspectorFiller : public PropertyFiller
    {
    public:
        explicit ElementInspectorFiller(event::ElementHandle handle_);
        void initProperties() override;

    private:
        event::ElementHandle handle;
    };
}
