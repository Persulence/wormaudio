#include "FakeModalDialogue.hpp"

#include "panel/BorderPanel.hpp"

namespace ui
{
    using namespace juce;

    FakeModalDialogue::FakeModalDialogue(std::shared_ptr<juce::Component> content_):
        content(std::move(content_))
    {
        dropShadow.radius = 5;
        dropShadow.offset = {0, 0};
        dropShadow.colour = juce::Colours::black;

        addAndMakeVisible(content.get());
    }

    void FakeModalDialogue::paint(juce::Graphics &g)
    {
        // paintBackground(g);
        dropShadow.drawForRectangle(g, content->getBounds());
    }

    void FakeModalDialogue::paintOverChildren(juce::Graphics &g)
    {
        g.setColour(Colours::white);
        Panel::paintBorder(g, content->getBounds(), 1);
    }

    void FakeModalDialogue::resized()
    {
        auto contentBounds = getLocalBounds().withSizeKeepingCentre(getHeight() * 0.7, getHeight() * 0.7);
        content->setBounds(contentBounds);
    }
}
