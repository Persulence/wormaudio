#include "StateNodeWidget.hpp"

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

    ConnectionCreationBox::ConnectionCreationBox(const StateConnectionManager::Ptr& manager_):
        manager(std::move(manager_))
    {

    }

    void ConnectionCreationBox::paint(juce::Graphics &g)
    {
        g.setColour(Colours::white);
        auto rect = getLocalBounds();
        rect.expand(10, 10);
        g.fillRect(rect);
    }

    void ConnectionCreationBox::mouseDown(const juce::MouseEvent &event)
    {
        manager->startConnection(getCentrePos());
    }

    void ConnectionCreationBox::mouseUp(const juce::MouseEvent &event)
    {
        manager->commitConnection(localPointToGlobal(event.position));
    }

    void ConnectionCreationBox::mouseDrag(const juce::MouseEvent &event)
    {
        manager->updateConnection(localPointToGlobal(event.position));
    }

    juce::Point<float> ConnectionCreationBox::getCentrePos() const
    {
        auto centre = localPointToGlobal(getLocalBounds().getCentre());
        return {static_cast<float>(centre.getX()), static_cast<float>(centre.getY())};
    }

    // StateNodeWidget

    StateNodeWidget::Ptr StateNodeWidget::create(const StateConnectionManager::Ptr& manager, juce::Point<int> pos)
    {
        auto ptr = std::make_shared<StateNodeWidget>(manager);
        ptr->setBounds(pos.x, pos.y, 150, 120);
        return ptr;
    }

    StateNodeWidget::StateNodeWidget(const StateConnectionManager::Ptr &connectionManager_):
        header(StateNodeHeader{}),
        connectionBox(connectionManager_)
    {
        addAndMakeVisible(header);
        addAndMakeVisible(connectionBox);
    }

    void StateNodeWidget::paint(Graphics &g)
    {
        g.setColour(Colours::grey);
        g.fillRect(getLocalBounds());
        g.setColour(Colours::black);
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
    }

    void StateNodeWidget::mouseUp(const juce::MouseEvent &event)
    {
        dragger.dragComponent(this, event, nullptr);
    }
}
