#include "StateCanvasPanel.hpp"
#include "StateNodeWidget.hpp"

using namespace juce;

namespace ui
{
    StateCanvasPanel::StateCanvasPanel():
        connectionManager(std::make_shared<StateConnectionManager>(this))
    {
        bg = Colours::darkgrey;

        // Create a node for testing
        addNode();
    }

    void StateCanvasPanel::addNode(const std::shared_ptr<StateNodeWidget>& node)
    {
        stateNodes.emplace_back(node);
        addAndMakeVisible(*node);
    }

    void StateCanvasPanel::addNode()
    {
        const auto centre = getLocalBounds().getCentre();
        addNode(StateNodeWidget::create(connectionManager, centre));
    }

    void StateCanvasPanel::removeNode(const std::shared_ptr<StateNodeWidget> &node)
    {
        if (const auto in = std::ranges::find(stateNodes, node); in != stateNodes.end())
        {
            stateNodes.erase(in);
        }
    }

    void StateCanvasPanel::paint(Graphics &g)
    {
        paintBackground(g);
        paintBorder(g);

        connectionManager->paint(g);
    }

    void StateCanvasPanel::mouseDown(const MouseEvent &event)
    {
        if (event.mods.isRightButtonDown())
        {
            PopupMenu menu;
            menu.addItem(1, "New state");
            // menu.addItem(2, "other thing");
            menu.showMenuAsync(PopupMenu::Options{},
                [this] (int result)
                {
                    switch (result)
                    {
                        case 1:
                        {
                            addNode();
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                });
        }
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
