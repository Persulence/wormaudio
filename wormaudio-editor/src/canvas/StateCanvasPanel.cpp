// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "StateCanvasPanel.hpp"
#include "StateNodeWidget.hpp"

#include <state/StateMachineDefinition.hpp>

#include "CanvasConnectionManager.hpp"
#include "command/Commands.hpp"
#include "editor/Editor.hpp"
#include "graph/StateDef.hpp"

using namespace juce;

namespace ui
{
    StateCanvasPanel::StateCanvasPanel():
        connectionManager(std::make_shared<CanvasConnectionManager>(&stateNodes, stateToNode)),
        definition(editor::Editor::getInstance().getEvent()->getDefinition())
    {
        for (auto& state : definition->getStates())
        {
            addNode(StateNodeWidget::create(state, connectionManager, Point(0, 0)));
        }

        addAndMakeVisible(connectionManager.get());
        connectionManager->toBack();
        connectionManager->refreshTransitionWidgets();

        // todo: FOR TESTING
        // auto node = addState({400, 400});
        // auto transition = std::make_shared<sm::Transition1>(condition::ConditionList{}, node->getState());
        // transition->conditions->insertCondition(condition::ComparisonCondition{});
        // definition->getStart()->insertTransition(transition);
        // connectionManager->refreshTransitionWidgets();

        // Commands
        commands()
            .add(CommandAction{Commands::DEL, [this](auto&){ removeSelectedNode();}})
            .add(CommandAction{Commands::RENAME, [this](auto&) { renameSelectedNode(); }})
            .finish();

        Commands::getInstance().getKeyMappings()->addKeyPress(Commands::DEL.id, KeyPress{KeyPress::deleteKey});
        Commands::getInstance().getKeyMappings()->addKeyPress(Commands::RENAME.id, KeyPress{KeyPress::F2Key});

        // Listen for runtime state changes
        editor::getInstance().onStateChange.setup(&stateChangeListener, [this](const auto& newState)
        {
            if (currentState)
            {
                currentState->setCurrent(false);
                currentState = nullptr;
            }

            if (auto it = stateToNode.find(newState); it != stateToNode.end())
            {
                it->second->setCurrent(true);
                currentState = it->second;
            }
        });

        editor::getInstance().onEventChanged.setup(&eventChangedListener, [this]
        {
            definition = editor::getInstance().getEvent()->getDefinition();

            stateNodes.clear();
            stateToNode.clear();

            for (auto& state : definition->getStates())
            {
                addNode(StateNodeWidget::create(state, connectionManager, Point(0, 0)));
            }

            connectionManager->refreshTransitionWidgets();
        });
    }

    StateNodeWidget::Ptr StateCanvasPanel::addNode(const std::shared_ptr<StateNodeWidget> &node)
    {
        stateNodes.emplace_back(node);
        stateToNode.emplace(node->getState(), node);
        addAndMakeVisible(node.get());

        connectionManager->toBack();

        updateCanvas(node);

        return node;
    }

    StateNodeWidget::Ptr StateCanvasPanel::addState(Point<int> pos)
    {
        auto state = std::make_shared<sm::StateDef>();

        definition->insert(state);

        // const auto centre = getLocalBounds().getCentre();
        return addNode(StateNodeWidget::create(state, connectionManager, pos));
    }

    void StateCanvasPanel::removeNode(const std::shared_ptr<StateNodeWidget> &node)
    {
        if (node->getState()->flags.type != sm::NORMAL)
            return;

        auto state = node->getState();

        definition->remove(state);

        removeChildComponent(node.get());
        if (const auto in = std::ranges::find(stateNodes, node); in != stateNodes.end())
            stateNodes.erase(in);

        if (const auto in = stateToNode.find(node->getState()); in != stateToNode.end())
            stateToNode.erase(in);

        if (auto selection = findParentComponentOfClass<CanvasSelectionManager>())
        {
            selection->select(nullptr);
        }

        connectionManager->repaint();
    }

    void StateCanvasPanel::paint(Graphics &g)
    {
        // paintBorder(g);
    }

    void StateCanvasPanel::resized()
    {
        connectionManager->setBounds(getBounds());
    }

    bool StateCanvasPanel::keyPressed(const KeyPress &key)
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

    void StateCanvasPanel::updateCanvas(const StateNodeWidget::Ptr &node)
    {
        if (getParentComponent() && !getLocalBounds().contains(node->getBounds()))
        {
            auto oldBounds = getBoundsInParent();
            auto localNewBounds = calculateBounds();
            auto parentNewBounds = getParentComponent()->getLocalArea(this, localNewBounds);

            auto delta = - parentNewBounds.getTopLeft() + oldBounds.getTopLeft();

            // Shift all nodes to compensate for the canvas position change
            for (auto& node1 : stateNodes)
            {
                node1->setTopLeftPosition(node1->getBounds().getTopLeft() + delta);
            }

            setBounds(parentNewBounds);
            connectionManager->setBounds(getLocalBounds());
        }
    }

    void StateCanvasPanel::contextMenu(Point<int> mousePos)
    {
        PopupMenu menu;
        menu.addItem(1, "New state");
        menu.showMenuAsync(PopupMenu::Options{}, [this, mousePos] (int result)
        {
            switch (result)
            {
                case 1:
                {
                    addState(mousePos);
                    break;
                }
                default:
                {
                    break;
                }
            }
        });
    }

    Rectangle<int> StateCanvasPanel::calculateBounds() const
    {
        if (stateNodes.empty())
            return Rectangle{0, 0, 0, 0};

        auto first = stateNodes.at(0);
        int minX = first->getX();
        int minY = first->getY();
        int maxX = first->getRight();
        int maxY = first->getBottom();

        for (auto& node : stateNodes)
        {
            auto bounds = node->getBounds();
            if (bounds.getX() < minX)
                minX = bounds.getX();

            if (bounds.getY() < minY)
                minY = bounds.getY();

            if (bounds.getRight() > maxX)
                maxX = bounds.getRight();

            if (bounds.getBottom() > maxY)
                maxY = bounds.getBottom();
        }

        return Rectangle<int>::leftTopRightBottom(minX, minY, maxX, maxY);
        // return Rectangle{0, 0, maxX - minX, maxY - minY};
    }

    void StateCanvasPanel::removeSelectedNode()
    {
        if (const auto manager = findParentComponentOfClass<CanvasSelectionManager>())
        {
            if (const auto shared = manager->getCurrent<StateNodeWidget>())
                removeNode(shared);
        }
    }

    void StateCanvasPanel::renameSelectedNode() const
    {
        if (const auto manager = findParentComponentOfClass<CanvasSelectionManager>())
        {
            if (const auto shared = manager->getCurrent<StateNodeWidget>())
                shared->rename();
        }
    }

    // ApplicationCommandTarget * StateCanvasPanel::getNextCommandTarget()
    // {
    //     return findFirstTargetParentComponent();
    // }
    //
    // void StateCanvasPanel::getAllCommands(Array<int> &commands)
    // {
    //     commands.add(ui::Commands::DEL);
    // }
    //
    // void StateCanvasPanel::getCommandInfo(CommandID commandID, ApplicationCommandInfo &result)
    // {
    //     switch (commandID)
    //     {
    //         case ui::Commands::DEL:
    //             result.setInfo("Delete node", "Delete selected node", "Node", 0);
    //     }
    // }

    // bool StateCanvasPanel::perform(const InvocationInfo &info)
    // {
    //     switch (info.commandID)
    //     {
    //         case Commands::DEL:
    //             const auto manager = findParentComponentOfClass<CanvasSelectionManager>();
    //             if (manager)
    //             {
    //                 if (auto shared = manager->getCurrent<StateNodeWidget>())
    //                     removeNode(shared);
    //
    //                 return true;
    //             }
    //     }
    //
    //     return false;
    // }
}
