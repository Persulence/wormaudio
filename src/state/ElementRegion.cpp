#include "ElementRegion.hpp"

namespace ui
{
    using namespace juce;

    void ElementRegion::paint(Graphics &g)
    {
        float cornerSize = 5;
        g.setColour(Colours::rebeccapurple);
        g.fillRoundedRectangle(getLocalBounds().toFloat(), cornerSize);
        g.setColour(Colours::mediumpurple);
        g.drawRoundedRectangle(getLocalBounds().toFloat(), cornerSize, 4);
    }
}
