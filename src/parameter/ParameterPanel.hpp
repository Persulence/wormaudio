#pragma once
#include "ParameterWidget.hpp"
#include "panel/Panel.hpp"

import parameter;

namespace ui
{
    class ParameterPanel : public Panel
    {
        parameter::Parameter testParameter;
        parameter::ParameterInstance testInstance;

        std::vector<std::unique_ptr<ParameterWidget>> widgets;

    public:
        explicit ParameterPanel();

        void refresh();

        void resized() override;
        void mouseDown(const juce::MouseEvent &event) override;
    };
}
