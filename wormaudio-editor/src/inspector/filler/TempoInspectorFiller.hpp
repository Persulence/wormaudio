// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "property/PropertyFiller.hpp"
#include "util/Data.hpp"
#include "util/Time.hpp"

namespace ui
{
    class TempoInspectorFiller : public PropertyFiller
    {
    public:
        explicit TempoInspectorFiller(player::Tempo &tempo_);

        void initProperties() override;

        player::Tempo& tempo;
    };
}
