#include "UiMainComponent.hpp"

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_opengl/opengl/juce_gl.h>

#include "theme/MainLookAndFeel.hpp"
#include "panel/BorderPanel.hpp"

using namespace juce;

namespace ui
{
    LeftPanel::LeftPanel():
        bar(&layout, 1, false)
    {
        // addAndMakeVisible(withNoname<BorderPanel>(fileBrowser));
        // addAndMakeVisible(withNoname<BorderPanel>(elementBrowser));
        addAndMakeVisible(fileBrowserBorder);
        addAndMakeVisible(elementBrowserBorder);
        addAndMakeVisible(bar);

        layout.setItemLayout(0, -0.1, -0.9, -0.5);
        layout.setItemLayout(1, 5, 5, 5);
        layout.setItemLayout(2, -0.1, -0.9, -0.5);
    }

    void LeftPanel::paint(juce::Graphics &g)
    {
        // paintBackground(g);
        // paintBorder(g);
    }

    void LeftPanel::resized()
    {
        // FlexBox flexBox;
        // flexBox.flexDirection = FlexBox::Direction::column;
        // flexBox.items.add(FlexItem(fileBrowserBorder).withFlex(100));
        // flexBox.items.add(FlexItem(elementBrowserBorder).withFlex(100));
        // flexBox.performLayout(getLocalBounds());

        std::array<Component*, 3> comps = {&fileBrowserBorder, &bar, &elementBrowserBorder};
        layout.layOutComponents(comps.begin(), comps.size(), 0, 0, getWidth(), getHeight(), true, true);
    }

    UiMainComponent::UiMainComponent():
        // leftHandle(ResizeHandle{ResizeHandle::Direction::VERTICAL, 250})
        bar(&layout, 1, true)
    {
        LookAndFeel::setDefaultLookAndFeel(&MainLookAndFeel::getInstance());

        addAndMakeVisible(leftPanel);
        addAndMakeVisible(centrePanel);
        // addAndMakeVisible(leftHandle);
        addAndMakeVisible(bar);

        // leftHandle.drag.emplace_back([this](float current)
        // {
        //     resized();
        // });

        layout.setItemLayout(0, -0.2, -0.9, -0.2);
        layout.setItemLayout(1, 5, 5, 5);
        layout.setItemLayout(2, -0.2, -0.9, -0.8);
    }

    void UiMainComponent::resized()
    {
        std::array<Component*, 3> comps = {&leftPanel, &bar, &centrePanel};
        layout.layOutComponents(comps.begin(), comps.size(), 0, 0,  getWidth(), getHeight(), false, true);


        // FlexBox leftPanelBox;
        // leftPanelBox.flexWrap = FlexBox::Wrap::noWrap;
        // leftPanelBox.flexDirection = FlexBox::Direction::row;
        // leftPanelBox.alignContent = FlexBox::AlignContent::stretch;
        // leftPanelBox.items.add(FlexItem(leftPanel).withMinWidth(leftHandle.currentPosition - 10).withMinHeight(
        //         static_cast<float>(getLocalBounds().getHeight())));
        // leftPanelBox.items.add(leftHandle.asFlexItem().withMinHeight(
        //         static_cast<float>(getLocalBounds().getHeight())));
        //
        // FlexBox horizontalStack;
        // horizontalStack.flexWrap = FlexBox::Wrap::noWrap;
        // horizontalStack.flexDirection = FlexBox::Direction::row;
        // horizontalStack.alignContent = FlexBox::AlignContent::stretch;
        // horizontalStack.justifyContent = FlexBox::JustifyContent::flexStart;
        // horizontalStack.alignItems = FlexBox::AlignItems::stretch;
        // // horizontalStack.items.add(FlexItem(leftPanelBox).withMinWidth(250).withMinHeight(getLocalBounds().getHeight()));
        // horizontalStack.items.add(FlexItem(leftPanelBox).withMinWidth(leftHandle
        //     .currentPosition).withMinHeight(
        //     static_cast<float>(getLocalBounds().getHeight())));
        // horizontalStack.items.add(FlexItem(centrePanel).withFlex(100).withMinWidth(500));
        // horizontalStack.performLayout(getLocalBounds());
    }

    // void setupLookAndFeel(juce::Component &component)
    // {
    //     Colour bg;
    //     component.getLookAndFeel().setColour()
    //     component.getLookAndFeel().setColour(juce::PopupMenu::backgroundColourId,);
    // }
}

