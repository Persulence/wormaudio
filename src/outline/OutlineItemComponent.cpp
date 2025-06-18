#include "OutlineItemComponent.hpp"

#include "util/GuiResources.hpp"

namespace ui
{
    using namespace juce;

    OutlineItemComponent::OutlineItemComponent(const std::string &icon):
        icon(juce::ImageCache::getFromFile(loadResource(icon)))
    {
        label.setEditable(false, true);

        addAndMakeVisible(label);
    }

    OutlineItemComponent::OutlineItemComponent():
        OutlineItemComponent("icon/resource.png")
    {
        label.setEditable(false, true);

        addAndMakeVisible(label);
    }

    void OutlineItemComponent::paint(juce::Graphics &g)
    {
        if (!icon.isNull())
        {
            g.drawImage(icon, iconBounds.toFloat(), RectanglePlacement::fillDestination, false);
        }
    }

    void OutlineItemComponent::resized()
    {
        auto bounds = getLocalBounds();
        iconBounds = bounds.removeFromLeft(getHeight()).reduced(4, 4);


        label.setBounds(bounds);
    }
}
