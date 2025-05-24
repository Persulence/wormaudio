#include "ElementRegion.hpp"

namespace ui
{
    using namespace juce;

    void ElementRegion::paint(juce::Graphics &g)
    {
        g.setColour(Colours::rebeccapurple);
        g.drawRoundedRectangle(getLocalBounds().toFloat(), 5, 2);
    }
}
