
#include "InspectorRoot.hpp"

namespace ui
{
    std::unique_ptr<InspectorRoot> InspectorRoot::wrap(std::unique_ptr<PropertyFiller> filler)
    {
        auto ptr = std::make_unique<InspectorRoot>();
        ptr->setFiller(std::move(filler));
        return ptr;
    }
}
