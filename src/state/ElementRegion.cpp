#include "ElementRegion.hpp"

namespace ui
{
    using namespace juce;

    void ElementRegion::paint(Graphics &g)
    {
        float cornerSize = 5;
        float thickness = 2;

        auto reduced = getLocalBounds().toFloat().reduced(thickness / 2);
        g.setColour(Colours::rebeccapurple);
        g.fillRoundedRectangle(reduced, cornerSize);
        g.setColour(Colours::mediumpurple);
        g.drawRoundedRectangle(reduced, cornerSize, thickness);

        g.setColour(Colours::black);
        g.drawText(element->getName(), getLocalBounds().withTrimmedLeft(10).toFloat(), Justification::centredLeft, true);
    }
}
