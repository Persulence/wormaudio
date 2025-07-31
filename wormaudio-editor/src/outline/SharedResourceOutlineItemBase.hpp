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

#pragma once

#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    class SharedResourceItemBase : public juce::TreeViewItem
    {
    public:
        virtual void createChildren() = 0;

        virtual bool remove() { return false; }

        virtual void rename() { };

        SharedResourceItemBase()
        {
            setLinesDrawnForSubItems(true);
        }

        template <class T>
        T* findSelectionManager()
        {
            if (const auto owner = getOwnerView())
            {
                return owner->findParentComponentOfClass<T>();
            }

            return nullptr;
        }

        void refresh(SharedResourceItemBase* origin = nullptr, bool strong = false)
        {
            if (strong)
            {
                if (const auto parent = dynamic_cast<SharedResourceItemBase*>(getParentItem()))
                {
                    parent->refresh(this, false);
                }
            }
            else
            {
                if (getOpenness() == Openness::opennessOpen)
                {
                    clearSubItems();
                    createChildren();
                }
                else
                {
                    clearSubItems();
                }
            }
        }

        void paintVerticalConnectingLine(juce::Graphics& g, const juce::Line<float> &line) override
        {
           // g.setColour(juce::Colours::black);
           // g.drawLine (line);
        }
    };
}

