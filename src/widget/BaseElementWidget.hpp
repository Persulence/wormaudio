#pragma once

#include "event/ElementHandle.hpp"
#include "juce_gui_basics/juce_gui_basics.h"
#include "util/selection/SelectionManager.hpp"

namespace ui
{
    class InspectorSelectionManager;

    class BaseElementWidget : public juce::Component, public SelectionTarget, public std::enable_shared_from_this<BaseElementWidget>
    {
    public:
        explicit BaseElementWidget(event::ElementHandle handle);
        void mouseDown(const juce::MouseEvent &event) override;

        std::shared_ptr<Component> createConfig() override;

    protected:
        event::ElementHandle handle;
    };
}
