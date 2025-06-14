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
        canvas.addMouseListener(this, false);

        // Set background colour. This will appear behind nodes.
        bg = Colours::darkgrey;

        setOpaque(true);
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

        // TODO
        const Point<int> pts[] = {canvasBounds.getTopLeft(), canvasBounds.getBottomRight(), minBounds.getTopLeft(), minBounds.getBottomRight()};
        auto rect = Rectangle<int>::findAreaContainingPoints(pts, 4);
        // canvas.setBoundsClever(rect);
        canvas.setBounds(rect);
    }

    void CanvasViewport::paint(juce::Graphics &g)
    {
        paintBackground(g);
    }

    void CanvasViewport::mouseDown(const MouseEvent &event)
    {
        if (event.mods.isRightButtonDown())
        {
            auto point = Point(event.x, event.y);

            // Event source can be this or the canvas.
            point = canvas.getLocalPoint(event.eventComponent, point);
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
