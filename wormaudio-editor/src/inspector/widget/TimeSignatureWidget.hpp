// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once
#include "property/PropertyWidget.hpp"
#include "util/Data.hpp"
#include "util/Time.hpp"
#include "util/component/MyLabel.hpp"

namespace ui
{
    class TimeSignatureWidget : public PropertyMember, util::Data<player::TimeSignature>::Listener
    {
    public:
        explicit TimeSignatureWidget(util::Data<player::TimeSignature> timeSignature);

        int getDesiredHeight() const override;

        void resized() override;
        void paint(juce::Graphics &g) override;

        DISABLE_COPY(TimeSignatureWidget)
        DISABLE_MOVE(TimeSignatureWidget)

    protected:
        util::Data<player::TimeSignature> timeSignature;

        MyLabel<int> numerator;
        MyLabel<int> denominator;

        void update();
    };

    class TimeSignaturePropertyWidget : public PropertyWidget
    {
    public:
        TimeSignaturePropertyWidget(const std::string &label, const util::Data<player::TimeSignature> &timeSignature) :
            PropertyWidget(label), backing(timeSignature)
        {
            addAndMakeVisible(backing);
        }

    protected:
        void setContentBounds(juce::Rectangle<int> bounds) override
        {
            backing.setBounds(bounds);
        }

        TimeSignatureWidget backing;
    };
}
