// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "TimeSignatureWidget.hpp"

#include <cassert>

namespace ui
{
    TimeSignatureWidget::TimeSignatureWidget(util::Data<player::TimeSignature> timeSignature_):
        timeSignature(std::move(timeSignature_)),
        numerator(parse::parseInt),
        denominator(parse::parseInt)
    {
        assert(timeSignature);

        addAndMakeVisible(numerator);
        numerator.setEditable(true);
        numerator.setJustificationType(juce::Justification::centred);
        numerator.onTextChange = [this]
        {
            auto sig = *timeSignature;
            sig.numerator = parse::parseInt(numerator.getText().toStdString());
            timeSignature = sig;
        };

        addAndMakeVisible(denominator);
        denominator.setEditable(true);
        denominator.setJustificationType(juce::Justification::centred);
        denominator.onTextChange = [this]
        {
            auto sig = *timeSignature;
            sig.denominator = parse::parseInt(denominator.getText().toStdString());
            timeSignature = sig;
        };

        update();

        timeSignature.setupListener(this, [this](auto& val)
        {
            update();
        });
    }

    int TimeSignatureWidget::getDesiredHeight() const
    {
        return settings::browserEntryHeight;
    }

    void TimeSignatureWidget::resized()
    {
        auto bounds = getLocalBounds();
        int width = getWidth() / 2.5;
        int centreWidth = getWidth() - 2 * width;

        numerator.setBounds(bounds.removeFromLeft(width));
        bounds.removeFromLeft(centreWidth);
        denominator.setBounds(bounds.removeFromLeft(width));
    }

    void TimeSignatureWidget::paint(juce::Graphics &g)
    {
        const auto centre = getLocalBounds().getCentre();
        g.setColour(getLookAndFeel().findColour(juce::Label::textColourId));
        g.drawText("/", centre.x - 15, 0, 30, getHeight(), juce::Justification::centred, false);
    }

    void TimeSignatureWidget::update()
    {
        const auto& sig = *timeSignature;

        numerator.setText(parse::defaultToString(sig.numerator), juce::dontSendNotification);
        denominator.setText(parse::defaultToString(sig.denominator), juce::dontSendNotification);
    }
}
