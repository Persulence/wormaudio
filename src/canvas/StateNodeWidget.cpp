#include "StateNodeWidget.hpp"


namespace ui
{
    using namespace juce;

    StateNodeHeader::StateNodeHeader()
    {
        setText("A state", dontSendNotification);
        setEditable(false, true);
        setJustificationType(Justification::left);
    }

    void StateNodeHeader::paint(juce::Graphics &g)
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

    // StateNodeWidget

    StateNodeWidget::Ptr StateNodeWidget::create(juce::Point<int> pos)
    {
        auto ptr = std::make_shared<StateNodeWidget>();
        ptr->setBounds(pos.x, pos.y, 150, 120);
        return ptr;
    }

    StateNodeWidget::StateNodeWidget():
        header(StateNodeHeader{})
    {
        addAndMakeVisible(header);
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
