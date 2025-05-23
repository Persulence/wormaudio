#include "UiMainComponent.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

using namespace juce;

namespace ui
{
    LeftPanel::LeftPanel()
    {
        addAndMakeVisible(fileBrowser);
        addAndMakeVisible(elementBrowser);
    }

    void LeftPanel::paint(juce::Graphics &g)
    {
        // paintBackground(g);
        // paintBorder(g);
    }

    void LeftPanel::resized()
    {
        FlexBox flexBox;
        flexBox.flexDirection = FlexBox::Direction::column;
        flexBox.items.add(FlexItem(fileBrowser).withFlex(100));
        flexBox.items.add(FlexItem(elementBrowser).withFlex(100));
        flexBox.performLayout(getLocalBounds());
    }

    UiMainComponent::UiMainComponent():
        leftHandle(ResizeHandle{ResizeHandle::Direction::VERTICAL, 250})
    {
        addAndMakeVisible(leftPanel);
        addAndMakeVisible(centrePanel);
        addAndMakeVisible(leftHandle);

        leftHandle.drag.emplace_back([this](float current)
        {
            resized();
        });

//        leftHandle.commit.emplace_back([this](float delta)
//        {
//            leftPanelWidth = currentLeftPanelWidth;
//            resized();
//        });
    }

    void UiMainComponent::resized()
    {
        using namespace juce;
        // juce::FlexBox fb;
        // fb.flexWrap = juce::FlexBox::Wrap::noWrap;
        // fb.flexDirection = juce::FlexBox::Direction::column;
        // fb.justifyContent = juce::FlexBox::JustifyContent::flexStart;
        // fb.alignContent = juce::FlexBox::AlignContent::stretch;
        //
        // fb.items.add(juce::FlexItem(b1).withMinWidth(50.0f).withMinHeight(50.0f));
        // fb.items.add(juce::FlexItem(b2).withMinWidth(50.0f).withMinHeight(50.0f));
        // fb.performLayout(getLocalBounds());

        FlexBox leftPanelBox;
        leftPanelBox.flexWrap = FlexBox::Wrap::noWrap;
        leftPanelBox.flexDirection = FlexBox::Direction::row;
        leftPanelBox.alignContent = FlexBox::AlignContent::stretch;
        leftPanelBox.items.add(FlexItem(leftPanel).withMinWidth(leftHandle.currentPosition - 10).withMinHeight(
                static_cast<float>(getLocalBounds().getHeight())));
        leftPanelBox.items.add(leftHandle.asFlexItem().withMinHeight(
                static_cast<float>(getLocalBounds().getHeight())));

        FlexBox horizontalStack;
        horizontalStack.flexWrap = FlexBox::Wrap::noWrap;
        horizontalStack.flexDirection = FlexBox::Direction::row;
        horizontalStack.alignContent = FlexBox::AlignContent::stretch;
        horizontalStack.justifyContent = FlexBox::JustifyContent::flexStart;
        horizontalStack.alignItems = FlexBox::AlignItems::stretch;
        // horizontalStack.items.add(FlexItem(leftPanelBox).withMinWidth(250).withMinHeight(getLocalBounds().getHeight()));
        horizontalStack.items.add(FlexItem(leftPanelBox).withMinWidth(leftHandle
            .currentPosition).withMinHeight(
            static_cast<float>(getLocalBounds().getHeight())));
        horizontalStack.items.add(FlexItem(centrePanel).withFlex(100).withMinWidth(500));
        horizontalStack.performLayout(getLocalBounds());
    }
}

