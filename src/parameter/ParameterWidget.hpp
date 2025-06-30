#pragma once

#include "ParameterConfigPanel.hpp"
#include "canvas/CanvasSelectionManager.hpp"
#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    class ParameterWidget : public juce::Component, public SelectionTarget, public ParameterProperties::OnChange::Listener, public std::enable_shared_from_this<ParameterWidget>
    {
        std::unique_ptr<Component> child;
        parameter::ParameterLookup& lookup;
        parameter::Parameter parameter;
        MyLabel<std::string> label;

    public:
        explicit ParameterWidget(parameter::ParameterLookup& lookup, parameter::Parameter parameter);
        void refresh();

        void resized() override;
        void mouseDown(const juce::MouseEvent &event) override;

    private:
        [[nodiscard]] parameter::ParameterInstance &getParameter() const;

    public:
        std::shared_ptr<Component> createConfig() override;

    private:
        std::unique_ptr<juce::FileChooser> c;
    };
}
