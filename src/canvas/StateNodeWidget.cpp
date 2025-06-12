#include "StateCanvasPanel.hpp"

#include <utility>

#include "StateNodeWidget.hpp"
#include "juce_graphics/juce_graphics.h"
#include "CanvasConnectionManager.hpp"
#include "browser/ElementDragSource.hpp"
#include "browser/FileListPanel.hpp"
#include "state/StatePropertyPanel.hpp"


namespace ui
{
    using namespace juce;

    StateNodeHeader::StateNodeHeader(StateNodeWidget& parent):
        parent(parent)
    {
        setText(parent.getState()->name, dontSendNotification);
        setEditable(false, true);
        setJustificationType(Justification::left);
        onTextChange = [this, &parent](){ parent.setName(getText()); };
    }

    void StateNodeHeader::paint(Graphics &g)
    {
        const auto type = parent.getState()->flags.type;
        const auto col = (type == sm::START || type == sm::END) ? Colours::darkred : Colours::darkblue;

        g.setColour(col);
        g.fillRect(getLocalBounds());

        Label::paint(g);
    }

    void StateNodeHeader::resized()
    {
        Label::resized();

        setFont(Font(FontOptions{static_cast<float>(getHeight()) - 2, Font::bold}));
    }

    void StateNodeHeader::updateName()
    {
        setText(parent.getState()->getName(), dontSendNotification);
    }

    void StateNodeHeader::mouseDown(const MouseEvent &event)
    {
        Label::mouseDown(event);
    }

    // ConnectionCreationBox

    StateNodeWidget::ConnectionCreationBox::ConnectionCreationBox(StateNodeWidget& parent_,
                                                                  CanvasConnectionManager::Ptr manager_) :
        manager(std::move(manager_)),
        parent(parent_)
    {

    }

    void StateNodeWidget::ConnectionCreationBox::paint(Graphics &g)
    {
        g.setColour(Colours::white);
        auto rect = getLocalBounds();
        rect.expand(10, 10);
        g.fillRect(rect);
    }

    void StateNodeWidget::ConnectionCreationBox::mouseDown(const MouseEvent &event)
    {
        manager->startConnection(getCentrePos());
//        manager->getDragAndDrop().startDragging(0, parent);
    }

    void StateNodeWidget::ConnectionCreationBox::mouseUp(const MouseEvent &event)
    {
        manager->commitConnection(localPointToGlobal(event.position));
    }

    void StateNodeWidget::ConnectionCreationBox::mouseDrag(const MouseEvent &event)
    {
        manager->updateConnection(localPointToGlobal(event.position));

        auto image = createComponentSnapshot (getLocalBounds(), true, 0.5f)
                .convertedToFormat (Image::ARGB);
        image.multiplyAllAlphas (0.6f);

        DragAndDropContainer::findParentDragContainerFor(this)->startDragging(
                0, &parent,
                image,
                false,
                nullptr,
                nullptr
                );
    }

    juce::Point<float> StateNodeWidget::ConnectionCreationBox::getCentrePos() const
    {
        auto centre = localPointToGlobal(getLocalBounds().getCentre());
        return {static_cast<float>(centre.getX()), static_cast<float>(centre.getY())};
    }

    // StateNodeWidget

    StateNodeWidget::StateNodeWidget(sm::StateDef::Ptr state_, CanvasConnectionManager::Ptr &connectionManager_):
        header(StateNodeHeader{*this}),
        connectionBox(ConnectionCreationBox{*this, connectionManager_}),
        manager(connectionManager_),
        state(std::move(state_))
    {
        addAndMakeVisible(header);
        addAndMakeVisible(connectionBox);
    }

    void StateNodeWidget::paint(Graphics &g)
    {
        g.setColour(Colours::grey);
        float corner = 4;
        auto reduced = getLocalBounds().toFloat().reduced(borderWidth / 2, borderWidth / 2);
        g.fillRoundedRectangle(reduced, corner);
        g.setColour(getBorderCol());
        g.drawRoundedRectangle(reduced, corner, borderWidth);
    }

    void StateNodeWidget::resized()
    {
        auto b = getLocalBounds();
        header.setBounds(b.removeFromTop(headerHeight));

        int boxDim = headerHeight;
        auto localBounds = getLocalBounds();
        Rectangle<int> boxBounds{
            localBounds.getX() + getWidth() - boxDim - borderWidth,
            localBounds.getY() + getHeight() - boxDim - borderWidth,
            boxDim,
            boxDim
        };

        connectionBox.setBounds(boxBounds);
    }

    void StateNodeWidget::setName(const String &newName)
    {
        Component::setName(newName);
        state->setName(newName.toStdString());
        header.updateName();
    }

    void StateNodeWidget::mouseDown(const MouseEvent &event)
    {
        if (event.mods.isLeftButtonDown())
        {
            dragger.startDraggingComponent(this, event);
            toFront(false);
            auto selectionManager = findParentComponentOfClass<CanvasSelectionManager>();
            if (selectionManager != nullptr)
            {
                selectionManager->select(shared_from_this());
            }
        }
    }

    void StateNodeWidget::mouseDrag(const juce::MouseEvent &event)
    {
        if (event.mods.isLeftButtonDown())
        {
            dragger.dragComponent(this, event, nullptr);
            findParentComponentOfClass<StateCanvasPanel>()->updateCanvas(shared_from_this());
            manager->setDraggingNode(true);
        }
    }

    void StateNodeWidget::mouseUp(const juce::MouseEvent &event)
    {
        // dragger.dragComponent(this, event, nullptr);
        manager->setDraggingNode(false);
    }

    bool StateNodeWidget::keyPressed(const juce::KeyPress &key)
    {
        // if (key.getKeyCode() == KeyPress::deleteKey)
        // {
        //     if (selected)
        //     {
        //         auto parent = findParentComponentOfClass<StateCanvasPanel>();
        //         if (parent != nullptr)
        //         {
        //             parent->removeNode(shared_from_this());
        //         }
        //     }
        // }

        return false;
    }

    sm::StateDef::Ptr& StateNodeWidget::getState()
    {
        return state;
    }

    std::shared_ptr<Component> StateNodeWidget::createConfig()
    {
        if (propertyComponent == nullptr)
        {
            const auto ptr = std::make_shared<StatePropertyPanel>(shared_from_this());

            propertyComponent = ptr;
        }
        return propertyComponent;
    }

    bool StateNodeWidget::isInterestedInDragSource(const DragAndDropTarget::SourceDetails &dragSourceDetails)
    {
        auto source = dragSourceDetails.sourceComponent.get();

        // A bit unpleasant, but it gets the job done
        if (dynamic_cast<StateNodeWidget*>(source))
            return true;

        if (dynamic_cast<FileDragSource*>(source))
            return true;

        if (dynamic_cast<ElementDragSource*>(source))
            return true;

        return false;
    }

    void StateNodeWidget::itemDropped(const SourceDetails &dragSourceDetails)
    {
        auto source = dragSourceDetails.sourceComponent.get();
        if (auto other = dynamic_cast<StateNodeWidget*>(source))
            manager->makeConnection(other, this);
        if (auto other = dynamic_cast<FileDragSource*>(source))
            dynamic_cast<StatePropertyPanel*>(createConfig().get())->receiveFile(other->getFile());
        if (auto other = dynamic_cast<ElementDragSource*>(source))
            dynamic_cast<StatePropertyPanel*>(createConfig().get())->receiveElement(other->getHandle());


        dragEnter = false;
        repaint();
    }


    void StateNodeWidget::itemDragEnter(const DragAndDropTarget::SourceDetails &dragSourceDetails)
    {
        dragEnter = true;
        repaint();
    }

    void StateNodeWidget::itemDragExit(const DragAndDropTarget::SourceDetails &dragSourceDetails)
    {
        dragEnter = false;
        repaint();
    }
}
