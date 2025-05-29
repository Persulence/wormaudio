#include "CanvasViewport.hpp"

using namespace juce;

namespace ui
{
    CanvasViewport::CanvasViewport()
    {
       // setViewedComponent(&canvas, false);
        addAndMakeVisible(canvas);
        // canvas.setVisible(true);
        canvas.setBounds(canvas.calculateBounds());

        // Get middle clicks for panning
        canvas.addMouseListener(this, true);
    }

    void CanvasViewport::resized()
    {
        const auto minBounds = getLocalBounds();
        const auto canvasBounds = canvas.calculateBounds();
        // const auto newBounds = minBounds.getUnion(canvasBounds);
        // if (minBounds.contains(canvasBounds))
        // {
        //     canvas.setBounds(getLocalBounds());
        // }
        // else
        // {
        //     auto rect = Rectangle<int>::leftTopRightBottom(minBounds.getX(), minBounds.getY(), canvasBounds.getRight(), canvasBounds.getBottom());
        //     canvas.setBounds(minBounds.getUnion(rect));
        // }
        // canvas.setBounds(canvasBounds);
        // childBoundsChanged();

        // setBounds(getParentComponent()->getLocalBounds());

        const Point<int> pts[] = {canvasBounds.getTopLeft(), canvasBounds.getBottomRight(), minBounds.getTopLeft(), minBounds.getBottomRight()};
        auto rect = Rectangle<int>::findAreaContainingPoints(pts, 4);
        // canvas.setBoundsClever(rect);
        canvas.setBounds(rect);

    }

    void CanvasViewport::mouseDown(const MouseEvent &event)
    {
        if (event.mods.isRightButtonDown())
        {
            auto point = Point(event.x, event.y);
            auto topLeft = canvas.getBounds().getTopLeft();

            if (event.eventComponent == this)
            {
                point = canvas.getLocalPoint(this, point);
            }

            canvas.contextMenu(point);
        }
        else if (event.mods.isMiddleButtonDown())
        {
            canvasDragger.startDraggingComponent(&canvas, event);
        }
    }

    void CanvasViewport::mouseDrag(const MouseEvent &event)
    {
        if (event.mods.isMiddleButtonDown())
        {
            canvasDragger.dragComponent(&canvas, event, nullptr);
        }
    }

}
