#pragma once
#include "ParameterWidget.hpp"
#include "editor/Editor.hpp"
#include "panel/Panel.hpp"

import parameter;
import control;

namespace ui
{
    class ParameterPanel : public Panel, public editor::Lifecycle::Listener
    {
        // parameter::Parameter testParameter;
        // parameter::ParameterInstance testInstance;

        std::vector<std::unique_ptr<ParameterWidget>> widgets;

    public:
        explicit ParameterPanel();

        void refresh();

        void resized() override;
        void mouseDown(const juce::MouseEvent &event) override;
    };
}
