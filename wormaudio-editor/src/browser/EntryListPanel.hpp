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

#include <cmath>
#include <algorithm>

#include "juce_gui_basics/juce_gui_basics.h"
#include "../panel/Panel.hpp"
#include "settings/settings.hpp"

namespace ui
{
    using EntryListCallback = std::function<void(int items)>;

    template <typename Entry>
    class EntryListPanel : public Panel
    {
    public:
        EntryListCallback callback = [](int){};

        explicit EntryListPanel(const int entryOffset_ = 0):
            entryOffset(entryOffset_)
        {

        }

        int getExpectedHeight() const
        {
            return expectedHeight;
        }

        void updateVisibilities()
        {
            const auto h = getEntryHeight();

            int hidden = 0;
            int visible = 0;

            const int offset = std::floor(entries.size() * std::min<double>(scrollFraction, 1.0));

            int i = entryOffset;
            for (const auto& element : entries)
            {
                // const auto elementY = element->getBoundsInParent().getY();

                // auto viewportArea = getParentComponent()->getBounds();
                // if (elementY < viewportArea.getY() || elementY > viewportArea.getBottom())
                auto parentHeight = getParentHeight();
                if (i >= offset && (i - offset) * h < parentHeight)
                {
                    element->setVisible(true);
                    element->setBounds(0, (i - offset) * h, getWidth(), h);
                    visible++;
                }
                else
                {
                    element->setVisible(false);
                    hidden++;
                }

                ++i;
            }

            // std::cout << "visible: " << visible << " hidden " << hidden << "\n";
        }

    protected:
        juce::Font font{juce::Font{juce::FontOptions{15}}};
        std::vector<std::shared_ptr<Entry>> entries;
        int entryH{settings::browserEntryHeight};
        int expectedHeight{entryH};

        const int entryOffset = 0;

        double scrollFraction{0};

        virtual int getEntryHeight()
        {
            return entryH;
        }

    };

}
