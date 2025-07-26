// Copyright (c) 2025 Persulence
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
        currentEvent(editor::getInstance().getEvent())
    {
        fillNodes();

        addAndMakeVisible(connectionManager.get());
        connectionManager->toBack();
        connectionManager->refreshTransitionWidgets();

        // Commands
        commands()
            .add(CommandAction{Commands::DEL, [this](auto&){ removeSelectedNode();}})
            .add(CommandAction{Commands::RENAME, [this](auto&) { renameSelectedNode(); }})
            .finish();

        Commands::getInstance().getKeyMappings()->addKeyPress(Commands::DEL.id, KeyPress{KeyPress::deleteKey});
        Commands::getInstance().getKeyMappings()->addKeyPress(Commands::RENAME.id, KeyPress{KeyPress::F2Key});

        auto& editor = editor::getInstance();

        // Listen for runtime state changes
        editor.onStateChange.setup(&stateChangeListener, [this](const auto& newState)
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

        editor.onEventChanged.setup(&eventChangedListener, [this]
        {
            auto& editor1 = editor::getInstance();

            // Save node positions
            editor1.getState().saveCanvas(currentEvent, saveNodePositions());

            currentEvent = editor1.getEvent();

            stateNodes.clear();
            stateToNode.clear();

            fillNodes();

            connectionManager->refreshTransitionWidgets();
        });

        editor.getState().beforeSave.setup(&beforeSaveListener, [this]
        {
            editor::getInstance().getState().saveCanvas(currentEvent, saveNodePositions());
        });
    }

    StateNodeWidget::Ptr StateCanvasPanel::addNode(const std::shared_ptr<StateNodeWidget> &node)
    {
        stateNodes.emplace_back(node);
        node->addMouseListener(this, true);
        stateToNode.emplace(node->getState(), node);
        addAndMakeVisible(node.get());

        connectionManager->toBack();

        updateCanvas(node);

        return node;
    }

    StateNodeWidget::Ptr StateCanvasPanel::addState(Point<int> pos)
    {
        auto state = std::make_shared<sm::StateDef>();

        currentEvent->getDefinition()->insert(state);

        // const auto centre = getLocalBounds().getCentre();
        return addNode(StateNodeWidget::create(state, connectionManager, pos));
    }

    void StateCanvasPanel::removeNode(const std::shared_ptr<StateNodeWidget> &node)
    {
        if (node->getState()->flags.type != sm::NORMAL)
            return;

        auto state = node->getState();

        currentEvent->getDefinition()->remove(state);

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

    void StateCanvasPanel::fillNodes()
    {
        auto canvasData = editor::getInstance().getState().getCanvas(currentEvent);
        for (auto& state : currentEvent->getDefinition()->getStates())
        {
            auto cornerPos = juce::Point{0, 0};
            if (canvasData)
            {
                if (const auto it = canvasData->nodes.find(state->getUUID()); it != canvasData->nodes.end())
                {
                    auto& [x, y] = it->second;
                    cornerPos = {x, y};
                }
            }

            const auto node = addNode(StateNodeWidget::create(state, connectionManager, cornerPos));
        }
    }

    editor::SoundCanvasData StateCanvasPanel::saveNodePositions() const
    {
        editor::SoundCanvasData data;

        for (auto& node : stateNodes)
        {
            const auto pos = node->getPosition();
            data.nodes.insert({node->getState()->getUUID(), {pos.x, pos.y}});
        }

        return data;
    }

    // void StateCanvasPanel::readNodePositions(const editor::SoundCanvasData &data) const
    // {
    //     for (auto& node : stateNodes)
    //     {
    //         if (const auto it = data.nodes.find(node->getState()->getUUID()); it != data.nodes.end())
    //         {
    //             const auto& [x, y] = it->second;
    //             node->setTopLeftPosition(x, y);
    //         }
    //     }
    // }

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
