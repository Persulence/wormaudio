#include "StateNodeWidget.hpp"


namespace ui
{
    using namespace juce;

    StateNodeHeader::StateNodeHeader()
    {
        setText("A state", dontSendNotification);
        setFont(Font(FontOptions{9.0f, Font::bold}));
        setJustificationType(Justification::left);
    }

    // StateNodeWidget

    StateNodeWidget::Ptr StateNodeWidget::create(juce::Point<int> pos)
    {
        auto ptr = std::make_shared<StateNodeWidget>();
        ptr->setBounds(pos.x, pos.y, 80, 60);
        return ptr;
    }

    StateNodeWidget::StateNodeWidget():
        header(StateNodeHeader{})
    {
        addAndMakeVisible(header);
    }

    void StateNodeWidget::paint(Graphics &g)
    {
        g.drawRect(getLocalBounds(), 1);
    }

    void StateNodeWidget::resized()
    {
        auto b = getLocalBounds();
        header.setBounds(b.removeFromTop(headerHeight));
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
