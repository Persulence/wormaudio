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
