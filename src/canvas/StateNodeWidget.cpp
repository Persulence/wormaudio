#include "StateCanvasPanel.hpp"

#include <utility>

#include "StateNodeWidget.hpp"
#include "juce_graphics/juce_graphics.h"
#include "CanvasConnectionManager.hpp"
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
        onTextChange = [this, &parent](){ parent.getState()->name = getText().toStdString(); };
    }

    void StateNodeHeader::paint(Graphics &g)
    {
        g.setColour(Colours::darkblue);
        g.fillRect(getLocalBounds());

        Label::paint(g);
    }

    void StateNodeHeader::resized()
    {
        Label::resized();

        setFont(Font(FontOptions{static_cast<float>(getHeight()) - 2, Font::bold}));
    }

    void StateNodeHeader::mouseDown(const juce::MouseEvent &event)
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

    StateNodeWidget::StateNodeWidget(sm::State::Ptr state_, CanvasConnectionManager::Ptr &connectionManager_):
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

    void StateNodeWidget::mouseDown(const juce::MouseEvent &event)
    {
        dragger.startDraggingComponent(this, event);
        toFront(false);
        auto selectionManager = findParentComponentOfClass<CanvasSelectionManager>();
        if (selectionManager != nullptr)
        {
            selectionManager->select(shared_from_this());
        }
    }

    void StateNodeWidget::mouseDrag(const juce::MouseEvent &event)
    {
        // if (event.x % 10 == 0 && event.y % 10 == 0)
        // {
            dragger.dragComponent(this, event, nullptr);
            manager->setDraggingNode(true);
        // }
    }

    void StateNodeWidget::mouseUp(const juce::MouseEvent &event)
    {
        dragger.dragComponent(this, event, nullptr);
        manager->setDraggingNode(false);
    }

    bool StateNodeWidget::keyPressed(const juce::KeyPress &key)
    {
        if (key.getKeyCode() == KeyPress::deleteKey)
        {
            if (selected)
            {
                auto parent = findParentComponentOfClass<StateCanvasPanel>();
                if (parent != nullptr)
                {
                    parent->removeNode(shared_from_this());
                }
            }
        }

        return false;
    }

    bool StateNodeWidget::isInterestedInDragSource(const DragAndDropTarget::SourceDetails &dragSourceDetails)
    {
        if (auto* other = dynamic_cast<StateNodeWidget*>(dragSourceDetails.sourceComponent.get()))
        {
            return true;
        }

        return false;
    }

    void StateNodeWidget::itemDropped(const DragAndDropTarget::SourceDetails &dragSourceDetails)
    {
        if (auto* other = dynamic_cast<StateNodeWidget*>(dragSourceDetails.sourceComponent.get()))
        {
            manager->makeConnection(other, this);
        }

        dragEnter = false;
    }

    sm::State::Ptr& StateNodeWidget::getState()
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

    void StateNodeWidget::itemDragEnter(const DragAndDropTarget::SourceDetails &dragSourceDetails)
    {
        dragEnter = true;
    }

    void StateNodeWidget::itemDragExit(const DragAndDropTarget::SourceDetails &dragSourceDetails)
    {
        dragEnter = false;
    }
}
