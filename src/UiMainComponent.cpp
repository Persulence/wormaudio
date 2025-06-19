#include "UiMainComponent.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

#include "theme/MainLookAndFeel.hpp"
#include "panel/BorderPanel.hpp"
#include "editor/Editor.hpp"

using namespace juce;

namespace ui
{
    LeftPanel::LeftPanel():
        elementBrowserBorder(BorderPanel<ElementBrowserPanel>{editor::getInstance().getEvent()}),
        bar1(&layout, 1, false),
        bar2(&layout, 3, false)
    {
        // addAndMakeVisible(withNoname<BorderPanel>(fileBrowser));
        // addAndMakeVisible(withNoname<BorderPanel>(elementBrowser));
        addAndMakeVisible(fileBrowserBorder);
        addAndMakeVisible(bar1);
        addAndMakeVisible(elementBrowserBorder);
        addAndMakeVisible(bar2);
        addAndMakeVisible(transport);

        layout.setItemLayout(0, -0.1, -0.9, -0.5);
        layout.setItemLayout(1, 5, 5, 5);
        layout.setItemLayout(2, -0.1, -0.9, -0.5);
        layout.setItemLayout(3, 5, 5, 5);
        layout.setItemLayout(4, -0.05, -0.05, -0.05);
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

        std::array<Component*, 5> comps = {&fileBrowserBorder, &bar1, &elementBrowserBorder, &bar2, &transport};
        layout.layOutComponents(comps.begin(), comps.size(), 0, 0, getWidth(), getHeight(), true, true);
    }

    MainSceneComponent::MainSceneComponent():
        rightPanel(*this),
        // leftHandle(ResizeHandle{ResizeHandle::Direction::VERTICAL, 250})
        bar1(&layout, 1, true),
        bar2(&layout, 3, true)
    {
        LookAndFeel::setDefaultLookAndFeel(&MainLookAndFeel::getInstance());

        addAndMakeVisible(leftPanel);
        addAndMakeVisible(centrePanel);
        addAndMakeVisible(rightPanel);
        addAndMakeVisible(bar1);
        addAndMakeVisible(bar2);

        layout.setItemLayout(0, -0.2, -0.9, -0.2);
        layout.setItemLayout(1, 5, 5, 5);
        layout.setItemLayout(2, -0.2, -0.9, -0.8);
        layout.setItemLayout(3, 5, 5, 5);
        layout.setItemLayout(4, -0.1, -0.9, -0.2);
    }

    void MainSceneComponent::resized()
    {
        std::array<Component*, 5> comps = {&leftPanel, &bar1, &centrePanel, &bar2, &rightPanel};
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

    UiMainComponent::UiMainComponent()
    {
        addAndMakeVisible(toolbar);
        addAndMakeVisible(mainScene);

        auto& editor = editor::Editor::getInstance();
        editor.startRuntime();
        editor.getRuntime().connectToDevice();
    }

    UiMainComponent::~UiMainComponent()
    {
        auto& editor = editor::Editor::getInstance();
        editor.shutdown();
    }

    void UiMainComponent::resized()
    {
        FlexBox box;
        box.flexDirection = FlexBox::Direction::column;
        box.justifyContent = FlexBox::JustifyContent::flexStart;
        box.alignContent = FlexBox::AlignContent::stretch;
        box.alignItems = FlexBox::AlignItems::stretch;
        // box.items.add(FlexItem{toolbar}.withMaxHeight(30).withHeight(30));
        box.items.add(FlexItem{mainScene}.withFlex(2));
        box.performLayout(getLocalBounds());
    }
}

