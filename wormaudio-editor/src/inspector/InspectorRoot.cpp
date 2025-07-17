
// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
