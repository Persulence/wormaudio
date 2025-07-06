#pragma once
#include "juce_gui_basics/juce_gui_basics.h"
#include "panel/Panel.hpp"

namespace ui
{
    class SpatialSelectorWidget : public juce::Component
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
            const int minDim = std::min(getWidth(), getHeight());

            selector.setBounds(
                (getWidth() - minDim) / 2,
                (getHeight() - minDim) / 2,
                minDim, minDim);
        }

    private:
        SpatialSelectorWidget selector;
    };

}
