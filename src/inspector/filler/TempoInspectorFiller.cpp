#include "TempoInspectorFiller.hpp"

#include "inspector/widget/TimeSignatureWidget.hpp"
#include "util/parse.hpp"

namespace ui
{
    TempoInspectorFiller::TempoInspectorFiller(player::Tempo& tempo_):
        tempo(tempo_)
    {
        setHeader(std::make_unique<SectionHeader>("Tempo"));
    }

    void TempoInspectorFiller::initProperties()
    {
        add(std::make_unique<TimeSignaturePropertyWidget>("Time Signature", tempo.getTimeSig()));
        add(std::make_unique<DataEntryPropertyWidget<double>>("BPM", tempo.bpm, parse::parseBpm));
    }
}
