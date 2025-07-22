// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "TempoInspectorFiller.hpp"

#include "inspector/widget/TimeSignatureWidget.hpp"
#include "util/parse.hpp"
#include "panel/MyPropertyPanel.hpp"

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
