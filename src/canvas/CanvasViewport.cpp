#include "CanvasViewport.hpp"

using namespace juce;

namespace ui
{
    CanvasViewport::CanvasViewport()
    {
       setViewedComponent(&canvas, false);
       canvas.setBounds(0, 0, 2000, 2000);
    }

    void CanvasViewport::resized()
    {
        const auto minBounds = getLocalBounds();
        const auto canvasBounds = canvas.calculateBounds();
        // const auto newBounds = minBounds.getUnion(canvasBounds);
        if (minBounds.contains(canvasBounds))
        {
            canvas.setBounds(getLocalBounds());
        }
        else
        {
            auto rect = Rectangle<int>::leftTopRightBottom(minBounds.getX(), minBounds.getY(), canvasBounds.getRight(), canvasBounds.getBottom());
            canvas.setBounds(minBounds.getUnion(rect));
        }
        // canvas.setBounds(canvasBounds);
        // childBoundsChanged();

        // setBounds(getParentComponent()->getLocalBounds());
        repaint();
    }
}
