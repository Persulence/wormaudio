#include "MainSceneComponent.hpp"

namespace ui
{
    using namespace juce;

    LeftPanel::LeftPanel():
        // elementBrowserBorder(BorderPanel<ElementBrowserPanel>{editor::getInstance().getEvent()}),
        bar1(&layout, 1, false),
        bar2(&layout, 3, false)
    {
        // addAndMakeVisible(withNoname<BorderPanel>(fileBrowser));
        // addAndMakeVisible(withNoname<BorderPanel>(elementBrowser));
        addAndMakeVisible(fileBrowserBorder);
        addAndMakeVisible(bar1);
        addAndMakeVisible(outline);
        addAndMakeVisible(bar2);
        addAndMakeVisible(transport);

        layout.setItemLayout(0, -0.1, -0.9, -0.5);
        layout.setItemLayout(1, 5, 5, 5);
        layout.setItemLayout(2, -0.1, -0.9, -0.5);
        layout.setItemLayout(3, 5, 5, 5);
        layout.setItemLayout(4, -0.05, -0.05, -0.05);
    }

    void LeftPanel::paint(Graphics &g)
    {
    }

    void LeftPanel::resized()
    {
        std::array<Component*, 5> comps{{&fileBrowserBorder, &bar1, &outline, &bar2, &transport}};
        layout.layOutComponents(comps.begin(), comps.size(), 0, 0, getWidth(), getHeight(), true, true);
    }



    RightPanel::RightPanel(InspectorSelectionManager &manager):
        inspector(manager),
        bar(&layout, 1, false)
    {
        addAndMakeVisible(inspector);
        addAndMakeVisible(spatial);
        addAndMakeVisible(bar);
        layout.setItemLayout(0, -0.1, -0.9, -0.8);
        layout.setItemLayout(1, 5, 5, 5);
        layout.setItemLayout(2, -0.1, -0.9, -0.2);
    }

    void RightPanel::resized()
    {
        std::array<Component*, 3> comps = {{&inspector, &bar, &spatial}};
        layout.layOutComponents(comps.begin(), comps.size(), 0, 0, getWidth(), getHeight(), true, true);
    }



    MainSceneComponent::MainSceneComponent():
        rightPanel(*this),
        // leftHandle(ResizeHandle{ResizeHandle::Direction::VERTICAL, 250})
        bar1(&layout, 1, true),
        bar2(&layout, 3, true)
    {
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

        editor::getInstance().onEventChanged.setup(&eventChangedListener, [this]
        {
            deselectAll();
        });
    }

    void MainSceneComponent::resized()
    {
        std::array<Component*, 5> comps = {{&leftPanel, &bar1, &centrePanel, &bar2, &rightPanel}};
        layout.layOutComponents(comps.begin(), comps.size(), 0, 0,  getWidth(), getHeight(), false, true);
    }
}
