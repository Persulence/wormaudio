#include "TransitionWidget.hpp"

#include "StateNodeWidget.hpp"
#include "transition/TransitionPropertyPanel.hpp"

namespace ui
{
    using namespace juce;

    void TransitionWidget::setNodes(const StateNodeWidget::Ptr &from_, const StateNodeWidget::Ptr &to_)
    {
        from = from_ ;
        to = to_;

        updateBounds();

        repaint();
    }

    void TransitionWidget::updateBounds()
    {
        const auto sharedFrom = from.lock();
        const auto sharedTo = to.lock();
        if (sharedFrom && sharedTo)
        {
            // Get points in parent component
            Point startPoint = getParentComponent()->getLocalPoint(sharedFrom.get(), sharedFrom->getLocalBounds().getCentre().toFloat());
            Point endPoint = getParentComponent()->getLocalPoint(sharedTo.get(), sharedTo->getLocalBounds().getCentre().toFloat());

            Point<float> p[] = {startPoint, endPoint};
            // Expand so that the arrows aren't clipped when lines are horizontal or vertical
            auto parentRect = Rectangle<float>::findAreaContainingPoints(p, 2)
                .expanded(10);
            setBounds(parentRect.toNearestInt());
        }
    }

    void TransitionWidget::paint(Graphics &g)
    {
        // g.fillRect(getLocalBounds()); // debug
        const auto sharedFrom = from.lock();
        const auto sharedTo = to.lock();
        if (sharedFrom && sharedTo)
        {
            Point startPoint = getLocalPoint(sharedFrom.get(), sharedFrom->getLocalBounds().getCentre().toFloat());
            Point endPoint = getLocalPoint(sharedTo.get(), sharedTo->getLocalBounds().getCentre().toFloat());

            auto vector = endPoint - startPoint;
            float len = sqrtf(vector.x * vector.x + vector.y * vector.y);

            // Skip unnecessarily short lines and divide by zeros
            if (len <= 1)
                return;

            // Offset lines if there is a two-way transition
            if (sharedTo->getState()->getTransitions().contains(sharedFrom->getState().get()))
            {
                float offset = 20;

                // Get normalised vector perpendicular to the line
                auto perp = Point(vector.y, -vector.x);
                perp = (perp / len) * offset;

                startPoint += perp;
                endPoint += perp;
            }

            auto vector1 = endPoint - startPoint;
            const auto line1 = Line(startPoint, startPoint + vector1 / 2);
            const auto line2 = Line(startPoint + vector1 / 2, endPoint);

            float thickness = 2;
            float arrowSize = 15;
            g.setColour(Colours::green);
            g.drawArrow(line1, thickness, arrowSize, arrowSize);
            g.drawLine(line2, thickness);
        }
    }

    void TransitionWidget::mouseDown(const MouseEvent &event)
    {
        Component::mouseDown(event);
    }

    std::shared_ptr<Component> TransitionWidget::createConfig()
    {
        return std::make_shared<TransitionPropertyPanel>(nullptr);
    }

    void TransitionWidget::onSelect()
    {

    }

    void TransitionWidget::onDeselect()
    {

    }
}
