// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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

