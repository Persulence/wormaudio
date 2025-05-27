#include "StateCanvasPanel.hpp"
#include "StateNodeWidget.hpp"

#include <control/StateMachineDefinition.hpp>

#include "editor/Editor.hpp"

import control;

using namespace juce;

namespace ui
{
    StateCanvasPanel::StateCanvasPanel():
        connectionManager(std::make_shared<CanvasConnectionManager>(&stateNodes, stateToNode)),
        definition(editor::Editor::getInstance().getDefinition())
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
        auto state = std::make_shared<sm::State>();
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

        if (auto selection = findParentComponentOfClass<CanvasSelectionManager>())
        {
            selection->select(nullptr);
        }
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
            contextMenu();
        }
    }

    void StateCanvasPanel::resized()
    {
        connectionManager->setBounds(getBounds());
    }

    bool StateCanvasPanel::keyPressed(const juce::KeyPress &key)
    {
        // if (key.getKeyCode() == KeyPress::deleteKey)
        // {
        //     auto selectionManager = findParentComponentOfClass<CanvasSelectionManager>();
        //     if (selectionManager != nullptr)
        //     {
        //         auto ptr = selectionManager->getCurrent();
        //         if (auto shared = ptr.lock(); shared != nullptr)
        //         {
        //             removeNode(shared);
        //         }
        //         return true;
        //     }
        // }

        return false;
    }

    void StateCanvasPanel::contextMenu()
    {
        PopupMenu menu;
        menu.addItem(1, "New state");
        menu.showMenuAsync(PopupMenu::Options{}, [this] (int result)
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
