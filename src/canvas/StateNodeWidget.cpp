#include "StateNodeWidget.hpp"
#include "juce_graphics/juce_graphics.h"
#include "StateConnectionManager.hpp"

#include <utility>

namespace ui
{
    using namespace juce;

    StateNodeHeader::StateNodeHeader()
    {
        setText("State", dontSendNotification);
        setEditable(false, true);
        setJustificationType(Justification::left);
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

    StateNodeWidget::ConnectionCreationBox::ConnectionCreationBox(StateNodeWidget* parent_,
                                                                  StateConnectionManager::Ptr manager_) :
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
                0, parent,
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

    StateNodeWidget::Ptr StateNodeWidget::create(const sm::State::Ptr& state, StateConnectionManager::Ptr &manager, Point<int> pos)
    {
        auto ptr = std::make_shared<StateNodeWidget>(state, manager);
        ptr->setBounds(pos.x, pos.y, 150, 120);
        return ptr;
    }

    StateNodeWidget::StateNodeWidget(sm::State::Ptr state_, StateConnectionManager::Ptr &connectionManager_):
        header(StateNodeHeader{}),
        connectionBox(ConnectionCreationBox{this, connectionManager_}),
        manager(connectionManager_),
        state(std::move(state_))
    {
        addAndMakeVisible(header);
        addAndMakeVisible(connectionBox);
    }

    void StateNodeWidget::paint(Graphics &g)
    {
        g.setColour(Colours::grey);
        g.fillRect(getLocalBounds());
        g.setColour(borderCol);
        g.drawRect(getLocalBounds(), 1);
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
    }

    void StateNodeWidget::mouseDrag(const juce::MouseEvent &event)
    {
        dragger.dragComponent(this, event, nullptr);
        manager->setDraggingNode(true);
    }

    void StateNodeWidget::mouseUp(const juce::MouseEvent &event)
    {
        dragger.dragComponent(this, event, nullptr);
        manager->setDraggingNode(false);
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

        borderCol = Colours::black;
    }

    sm::State::Ptr& StateNodeWidget::getState()
    {
        return state;
    }

    void StateNodeWidget::itemDragEnter(const DragAndDropTarget::SourceDetails &dragSourceDetails)
    {
        borderCol = Colours::red;
    }

    void StateNodeWidget::itemDragExit(const DragAndDropTarget::SourceDetails &dragSourceDetails)
    {
        borderCol = Colours::black;
    }
}
