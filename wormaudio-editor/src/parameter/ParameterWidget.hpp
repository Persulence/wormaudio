// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
