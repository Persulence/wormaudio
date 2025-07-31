// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
