#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "settings/settings.hpp"

namespace ui
{
    class PropertyMember : public juce::Component
    {
    public:
        enum RefreshLevel
        {
            /// This member should be reinitialised.
            SOFT,

            /// This member should be completely reconstructed by the parent member.
            HARD
        };

        virtual float getDesiredHeight() const = 0;
        virtual float getDesiredLabelWidth() const { return 0; };
        virtual void setLabelWidth(float labelWidth_) { }
    };

    class PropertyWidget : public PropertyMember
    {
    public:
        explicit PropertyWidget(std::string label);
        float getDesiredLabelWidth() const override;
        void setLabelWidth(float labelWidth_) override;
        float getDesiredHeight() const override { return settings::browserEntryHeight; }

        void resized() override;
        void paint(juce::Graphics &g) override;

    protected:
        virtual void setContentBounds(juce::Rectangle<int> bounds) = 0;

    private:
        std::string label;
        float labelWidth;

        juce::Label labelComponent;
    };
}
