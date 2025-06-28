#include "TempoInspectorFiller.hpp"

namespace ui
{
    TempoInspectorFiller::TempoInspectorFiller(util::Data<player::Tempo> tempo_):
        tempo(std::move(tempo_))
    {
        setHeader(std::make_unique<SectionHeader>("Tempo"));
    }

    void TempoInspectorFiller::initProperties()
    {

    }
}
