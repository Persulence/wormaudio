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

#include <signal/Listener.hpp>

#include "editor/Editor.fwd.hpp"
#include "juce_gui_basics/juce_gui_basics.h"
#include "panel/Panel.hpp"

namespace ui
{
    class SpatialSelectorWidget : public juce::Component, editor::EventChanged::Listener
    {
    public:
        SpatialSelectorWidget();

        void paint(juce::Graphics &g) override;
        void resized() override;

        void mouseDown(const juce::MouseEvent &event) override;
        void mouseDrag(const juce::MouseEvent &event) override;
        void mouseDoubleClick(const juce::MouseEvent &event) override;

    private:
        void updatePosition(juce::Point<float> point);
        void setSoundPosition(float x, float z);

        float diameter;
        juce::Point<float> sourcePos;
    };

    class SpatialPreviewPanel : public Panel
    {
    public:
        SpatialPreviewPanel()
        {
            addAndMakeVisible(selector);
        }

        void paint(juce::Graphics &g) override
        {
            paintBackground(g);
        }

        void resized() override
        {
            const int minDim = std::min<double>(getWidth(), getHeight());

            selector.setBounds(
                (getWidth() - minDim) / 2,
                (getHeight() - minDim) / 2,
                minDim, minDim);
        }

    private:
        SpatialSelectorWidget selector;
    };

}
