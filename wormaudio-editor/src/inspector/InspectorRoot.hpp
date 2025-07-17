// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "property/PropertyFiller.hpp"

namespace ui
{
    class InspectorRoot : public juce::Component
    {
    public:
        static std::unique_ptr<InspectorRoot> wrap(std::unique_ptr<PropertyFiller> filler);

        void setFiller(std::unique_ptr<PropertyFiller> filler_)
        {
            removeAllChildren();
            filler = std::move(filler_);
            filler->initProperties();
            addAndMakeVisible(filler.get());
        }

        void resized() override
        {
            if (filler)
            {
                filler->setBounds(getLocalBounds());
            }
        }

        int getDesiredHeight() const
        {
            if (filler)
            {
                return filler->getDesiredHeight();
            }

            return getHeight();
        }

    private:
        std::unique_ptr<PropertyFiller> filler;
    };
}
