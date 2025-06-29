#include "TempoInspectorFiller.hpp"

#include "inspector/widget/TimeSignatureWidget.hpp"
#include "util/parse.hpp"

namespace ui
{
    TempoInspectorFiller::TempoInspectorFiller(player::Tempo& tempo_):
        tempo(std::move(tempo_))
    {
        setHeader(std::make_unique<SectionHeader>("Tempo"));
    }

    void TempoInspectorFiller::initProperties()
    {
        add(std::make_unique<TimeSignaturePropertyWidget>("Time Signature", tempo.timeSig));
    }
}
