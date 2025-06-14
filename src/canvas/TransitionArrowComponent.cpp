#include "TransitionArrowComponent.hpp"

#include "InspectorSelectionManager.hpp"
#include "StateNodeWidget.hpp"
#include "transition/TransitionPropertyPanel.hpp"

namespace ui
{

    using namespace juce;

    Point<float> twoWayOffset(const Point<float> vector)
    {
        constexpr float offset = 20;

        const auto perpendicular = Point(vector.y, -vector.x);

        const float len = sqrtf(vector.x * vector.x + vector.y * vector.y);
        return (perpendicular / len) * offset;
    }

    TransitionArrowComponent::TransitionArrowComponent()
    {
        setWantsKeyboardFocus(true);
        setMouseClickGrabsKeyboardFocus(true);
    }

    void TransitionArrowComponent::setNodes(const StateNodeWidget::Ptr &from_, const StateNodeWidget::Ptr &to_)
    {
        from = from_ ;
        to = to_;

        updateBounds();

        repaint();
    }

    std::tuple<StateNodeWidgetPtr, StateNodeWidgetPtr> TransitionArrowComponent::lock() const
    {
        const auto sharedFrom = from.lock();
        const auto sharedTo = to.lock();
        return {sharedFrom, sharedTo};
        // if (sharedFrom && sharedTo)
        // {
        // }

        // return {};
    }

    void TransitionArrowComponent::updateBounds()
    {
        const auto [sharedFrom, sharedTo] = lock();
        if (sharedFrom && sharedTo)
        {
            if (isSelf())
            {
                auto nodeBounds = sharedFrom->getLocalBounds();
                float shrink = nodeBounds.getWidth() * 0.1;
                auto bounds = Rectangle<float>{nodeBounds.getX() + shrink, static_cast<float>(nodeBounds.getY()) - 40.f, static_cast<float>(nodeBounds.getWidth()) - 2 * shrink, 40};
                // Rectangle bounds = nodeBounds.withTrimmedTop(-40);

                setBounds(getParentComponent()->getLocalArea(sharedFrom.get(), bounds.toNearestInt()));
            }
            else
            {
                // Get points in parent component
                Point startPoint = getParentComponent()->getLocalPoint(sharedFrom.get(), sharedFrom->getLocalBounds().getCentre().toFloat());
                Point endPoint = getParentComponent()->getLocalPoint(sharedTo.get(), sharedTo->getLocalBounds().getCentre().toFloat());

                if (isTwoWay())
                {
                    auto perp = twoWayOffset(endPoint - startPoint);
                    startPoint += perp;
                    endPoint += perp;
                }

                Point<float> p[] = {startPoint, endPoint};
                // Expand so that the arrows aren't clipped when lines are horizontal or vertical
                auto parentRect = Rectangle<float>::findAreaContainingPoints(p, 2)
                    .expanded(10);
                setBounds(parentRect.toNearestInt());
            }
        }
    }

    void drawSelfLine(Graphics& g, const Rectangle<int> local, const float thickness, const float arrowSize)
    {
        int h = 20;

        g.drawLine(local.getX(), local.getY() + h, local.getX(), local.getBottom(), thickness);
        g.drawLine(local.getRight(), local.getY() + h, local.getRight(), local.getBottom(), thickness);

        const auto line1 = Line{local.getX(), local.getY() + h, local.getRight(), local.getY() + h}.toFloat().reversed();
        g.drawArrow(line1.withShortenedEnd(line1.getLength() / 2), thickness, arrowSize, arrowSize);
        g.drawLine(line1.withShortenedStart(line1.getLength() / 2), thickness);
    }

    void TransitionArrowComponent::paint(Graphics &g)
    {
        const auto [sharedFrom, sharedTo] = lock();
        if (sharedFrom && sharedTo)
        {
            float const thickness = 2;
            float const arrowSize = 15;

            if (isSelf())
            {
                const auto local = getLocalBounds().expanded(-thickness, 0).withTrimmedTop(thickness);

                if (selected)
                {
                    g.setColour(Colours::white);
                    drawSelfLine(g, local, thickness * 2, arrowSize);
                }

                g.setColour(Colours::green);
                drawSelfLine(g, local, thickness, arrowSize);
            }
            else
            {
                Point startPoint = getLocalPoint(sharedFrom.get(), sharedFrom->getLocalBounds().getCentre().toFloat());
                Point endPoint = getLocalPoint(sharedTo.get(), sharedTo->getLocalBounds().getCentre().toFloat());

                auto vector = endPoint - startPoint;
                float len = sqrtf(vector.x * vector.x + vector.y * vector.y);

                // Skip unnecessarily short lines and divide by zeros
                if (len <= 20)
                    return;

                // Offset lines if there is a two-way transition
                if (isTwoWay())
                {
                    // Get normalised vector perpendicular to the line
                    const auto perp = twoWayOffset(vector);

                    startPoint += perp;
                    endPoint += perp;
                }

                auto vector1 = endPoint - startPoint;
                const auto line1 = Line(startPoint, startPoint + vector1 / 2);
                const auto line2 = Line(startPoint + vector1 / 2, endPoint);

                if (selected)
                {
                    g.setColour(Colours::white);
                    g.drawArrow(line1, thickness * 2, arrowSize, arrowSize);
                    g.drawLine(line2, thickness * 2);
                }

                g.setColour(Colours::green);
                g.drawArrow(line1, thickness, arrowSize, arrowSize);
                g.drawLine(line2, thickness);
            }
        }
    }

    bool TransitionArrowComponent::hitTest(int x, int y)
    {
        if (Component::hitTest(x, y))
        {
            if (isSelf())
            {
                return true;
            }
            else
            {
                const auto [sharedFrom, sharedTo] = lock();
                if (sharedFrom && sharedTo)
                {
                    Point startPoint = getLocalPoint(sharedFrom.get(), sharedFrom->getLocalBounds().getCentre().toFloat());
                    Point endPoint = getLocalPoint(sharedTo.get(), sharedTo->getLocalBounds().getCentre().toFloat());

                    if (isTwoWay())
                    {
                        auto perp = twoWayOffset(endPoint - startPoint);
                        startPoint += perp;
                        endPoint += perp;
                    }

                    // Convert line to 0 = ax + by + c
                    float m = (startPoint.y - endPoint.y) / (startPoint.x - endPoint.x);
                    float c = startPoint.y - m * startPoint.x;

                    float a = m;
                    float b = -1;

                    float distanceToLine = std::abs(a * x + b * y + c) / std::sqrt(a * a + b * b);

                    if (distanceToLine < 20)
                        return true;
                }
            }
        }
        return false;
    }

    void TransitionArrowComponent::mouseDown(const MouseEvent &event)
    {
        if (const auto manager = findParentComponentOfClass<InspectorSelectionManager>())
        {
            manager->select(shared_from_this());
        }
    }

    bool TransitionArrowComponent::keyPressed(const KeyPress &key)
    {
        return false;
    }

    bool TransitionArrowComponent::isTwoWay() const
    {
        if (const auto [sharedFrom, sharedTo] = lock(); sharedFrom && sharedTo)
        {
            if (sharedTo->getState()->getTransitions().contains(sharedFrom->getState().get()))
                return true;
        }

        return false;
    }

    bool TransitionArrowComponent::isSelf() const
    {
        return from.lock() == to.lock();
    }

    std::shared_ptr<Component> TransitionArrowComponent::createConfig()
    {
        const auto sharedFrom = from.lock();
        const auto sharedTo = to.lock();
        if (sharedFrom && sharedTo)
        {
            return std::make_shared<TransitionPropertyPanel>(sharedFrom->getState()->getTransitions().at(sharedTo->getState().get()));
        }

        // TODO
        throw std::exception{};
    }

    void TransitionArrowComponent::onSelect()
    {
        selected = true;
        repaint();
    }

    void TransitionArrowComponent::onDeselect()
    {
        selected = false;
        repaint();
    }

    // Colour TransitionWidget::getCol()
    // {
    //     return selected ? Colours::aliceblue : Colours::green;
    // }
}
