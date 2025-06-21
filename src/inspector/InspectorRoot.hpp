#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "property/PropertyFiller.hpp"

namespace ui
{
    class InspectorRoot : public juce::Component
    {
    public:
        static std::unique_ptr<InspectorRoot> wrap(std::unique_ptr<PropertyFiller> filler)
        {
            auto ptr = std::make_unique<InspectorRoot>();
            ptr->setFiller(std::move(filler));
            return ptr;
        }

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

    private:
        std::unique_ptr<PropertyFiller> filler;
    };
}
