#include "ResizeHandle.hpp"

using namespace ui;
using namespace juce;

ResizeHandle::ResizeHandle(Direction direction_, float position_, float width_, float margin_):
    direction(direction_),
    width(width_),
    position(position_),
    margin(margin_),
    currentPosition(position_)
{

}

void ResizeHandle::mouseDrag(const juce::MouseEvent &event)
{
    int dragged = choose<int>(direction, event.getDistanceFromDragStartY(), event.getDistanceFromDragStartX());

    // the horror
    auto majorDimension = static_cast<float>(choose(direction, getParentHeight(), getParentWidth()));
    currentPosition = std::clamp(position + static_cast<float>(dragged), margin, majorDimension - margin - width);

    for (const auto& callback : drag)
    {
        callback(currentPosition);
    }
}

void ResizeHandle::mouseUp(const MouseEvent &event)
{
    position = currentPosition;
    for (const auto& callback : commit)
    {
        callback(position);
    }
}

juce::FlexItem ResizeHandle::asFlexItem()
{
    switch (direction)
    {
        case Direction::HORIZONTAL:
        {
            return FlexItem{*this}.withMinHeight(width);
        }
        case Direction::VERTICAL:
        {
            return FlexItem{*this}.withMinWidth(width);
        }
    }
}

void ResizeHandle::paint(Graphics &g)
{
    g.setColour(juce::Colours::red);
    g.fillRect(getLocalBounds());
}

void ResizeHandle::resized()
{
//    std::cout << "handle resized\n";
}
