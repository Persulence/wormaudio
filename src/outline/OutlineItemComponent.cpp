#include "OutlineItemComponent.hpp"

#include "util/GuiResources.hpp"

namespace ui
{
    using namespace juce;

    OutlineItemComponent::OutlineItemComponent(juce::TreeViewItem* item_, const std::string &icon, bool editable):
        icon(ImageCache::getFromFile(loadResource(icon))), item(item_)
    {
        addAndMakeVisible(label);

        if (editable)
            label.setEditable(false, true);

        // label.getTextValue().referTo(name.value);
    }

    OutlineItemComponent::OutlineItemComponent(juce::TreeViewItem* item_):
        OutlineItemComponent(item_, "icon/resource.png", true)
    {
        label.setEditable(false, true);

        addAndMakeVisible(label);
    }

    void OutlineItemComponent::paint(juce::Graphics &g)
    {
        if (item->isSelected())
        {
            g.setColour(juce::Colours::darkblue);
            g.fillRect(getLocalBounds());
        }

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
