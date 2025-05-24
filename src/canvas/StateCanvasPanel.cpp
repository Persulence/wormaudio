#include "StateCanvasPanel.hpp"
#include "StateNodeWidget.hpp"

#include <control/StateMachineDefinition.hpp>

import control;

using namespace juce;

namespace ui
{
    StateCanvasPanel::StateCanvasPanel():
        connectionManager(std::make_shared<CanvasConnectionManager>(&stateNodes, stateToNode)),
        definition(std::make_shared<sm::StateMachineDefinition>())
    {
        setOpaque(true);

        bg = Colours::darkgrey;

        // Create a node for testing
        addNode();

        addAndMakeVisible(connectionManager.get());
        connectionManager->toBack();
    }

    void StateCanvasPanel::addNode(const std::shared_ptr<StateNodeWidget>& node)
    {
        stateNodes.emplace_back(node);
        stateToNode.emplace(node->getState(), node);
        addAndMakeVisible(node.get());

        connectionManager->toBack();
    }

    void StateCanvasPanel::addNode()
    {
        sm::State::Ptr state = std::make_shared<sm::State>();
        definition->insert(state);

        const auto centre = getLocalBounds().getCentre();
        addNode(StateNodeWidget::create(state, connectionManager, centre));
    }

    void StateCanvasPanel::removeNode(const std::shared_ptr<StateNodeWidget> &node)
    {
        removeChildComponent(node.get());
        if (const auto in = std::ranges::find(stateNodes, node); in != stateNodes.end())
            stateNodes.erase(in);

        if (const auto in = stateToNode.find(node->getState()); in != stateToNode.end())
            stateToNode.erase(in);
    }

    void StateCanvasPanel::paint(Graphics &g)
    {
        paintBackground(g);
        paintBorder(g);

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

    void StateCanvasPanel::resized()
    {
        connectionManager->setBounds(getBounds());
    }
}
