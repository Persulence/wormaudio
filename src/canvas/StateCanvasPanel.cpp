#include "StateCanvasPanel.hpp"

using namespace juce;

namespace ui
{
    void StateCanvasPanel::paint(juce::Graphics &g)
    {
        paintBackground(g);
        paintBorder(g);
    }

    void StateEditorPanel::paint(juce::Graphics &g)
    {
        paintBackground(g);
        paintBorder(g);
    }

    CentrePanel::CentrePanel()
    {
        addAndMakeVisible(canvas);
        addAndMakeVisible(editor);
    }

    void CentrePanel::resized()
    {
        FlexBox box;
        box.flexDirection = FlexBox::Direction::column;
        box.items.add(FlexItem(canvas).withMinHeight(200).withFlex(100));
        box.items.add(FlexItem(editor).withMinHeight(200));
        box.performLayout(getLocalBounds());
    }
}
