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
