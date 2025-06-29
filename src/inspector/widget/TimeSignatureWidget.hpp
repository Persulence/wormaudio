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
