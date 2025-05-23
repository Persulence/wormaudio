#include "StateCanvasPanel.hpp"
#include "StateNodeWidget.hpp"

using namespace juce;

namespace ui
{
    StateCanvasPanel::StateCanvasPanel()
    {
        bg = Colours::darkgrey;

        // Create a node for testing
        const auto centre = getLocalBounds().getCentre();
        addNode(StateNodeWidget::create(centre));
    }

    void StateCanvasPanel::addNode(std::shared_ptr<StateNodeWidget> node)
    {
        stateNodes.emplace_back(node);
        addAndMakeVisible(*node);
    }

    void StateCanvasPanel::removeNode(std::shared_ptr<StateNodeWidget> node)
    {
        if (const auto in = std::ranges::find(stateNodes, node); in != stateNodes.end())
        {
            stateNodes.erase(in);
        }
    }

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

    CentrePanel::CentrePanel():
        handle(ResizeHandle(ResizeHandle::Direction::HORIZONTAL, 500))
    {
        addAndMakeVisible(canvas);
        addAndMakeVisible(editor);
        addAndMakeVisible(handle);

        handle.drag.emplace_back([this](float f) {
            resized();
        });
    }

    void CentrePanel::resized()
    {
        FlexBox box;
        box.flexDirection = FlexBox::Direction::column;
        box.items.add(FlexItem(canvas).withMinHeight(handle.currentPosition));
        box.items.add(handle.asFlexItem());
        box.items.add(FlexItem(editor).withFlex(200));
        box.performLayout(getLocalBounds());
    }
}
