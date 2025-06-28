#pragma once
#include "property/PropertyFiller.hpp"
#include "util/Data.hpp"
#include "util/Time.hpp"

namespace ui
{
    class TempoInspectorFiller : public PropertyFiller
    {
    public:
        TempoInspectorFiller(util::Data<player::Tempo> tempo_);
        void initProperties() override;

        util::Data<player::Tempo> tempo;
    };
}
