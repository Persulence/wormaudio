// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
