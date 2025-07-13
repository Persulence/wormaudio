// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "ParameterWidget.hpp"
#include "editor/Editor.hpp"
#include "panel/Panel.hpp"

namespace ui
{
    class ParameterPanel : public Panel, public editor::Lifecycle::Listener, public editor::ParametersChanged::Listener
    {
        // parameter::Parameter testParameter;
        // parameter::ParameterInstance testInstance;

        std::vector<std::shared_ptr<ParameterWidget>> widgets;

    public:
        explicit ParameterPanel();

        void refresh();

        void paint(juce::Graphics &g) override;
        void resized() override;
        void mouseDown(const juce::MouseEvent &event) override;

    private:
        void addNewParameter(const parameter::Parameter &parameter);
    };
}
