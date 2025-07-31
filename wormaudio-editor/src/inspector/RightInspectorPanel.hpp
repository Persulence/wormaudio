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

#include "canvas/InspectorSelectionManager.hpp"

#include "panel/Panel.hpp"

namespace ui
{
    class RightInspectorPanel : public Panel
    {
        InspectorSelectionManager::ChangeCallback::Listener onSelect;
        InspectorSelectionManager::ChangeCallback::Listener onDeselectAll;

        std::mutex configMutex;
        std::shared_ptr<Component> configComponent;
        juce::Label helpText;

    public:
        explicit RightInspectorPanel(InspectorSelectionManager &manager):
            manager(manager)
        {
            onSelect.listen(manager.onSelect, [this]{ updateSelection(); });
            onDeselectAll.listen(manager.onDeselectAll, [this]{ updateSelection(); });

            addAndMakeVisible(helpText);
            helpText.setJustificationType(juce::Justification::centred);
            helpText.setText("No item selected", juce::dontSendNotification);
        }

        void updateSelection()
        {
            std::lock_guard lock{configMutex};
            if (configComponent)
            {
                removeChildComponent(configComponent.get());
            }

            if (const auto shared = manager.getCurrent().lock(); shared != nullptr)
            {
                configComponent = shared->createConfig();
                addAndMakeVisible(configComponent.get());
                configComponent->setBounds(getLocalBounds());
                helpText.setVisible(false);
                repaint();
            }
            else
            {
                configComponent = nullptr;
                helpText.setVisible(true);
            }
        }

        void paint(juce::Graphics &g) override
        {
            paintBackground(g);
        }

        void resized() override
        {
            if (configComponent != nullptr)
            {
                configComponent->setBounds(getLocalBounds());
            }

            helpText.setBounds(getLocalBounds());
        }

    private:
        InspectorSelectionManager& manager;
    };
}
