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

#include "StateNodeWidget.fwd.hpp"

#include "juce_gui_basics/juce_gui_basics.h"

#include "util/component/MyLabel.hpp"
#include "CanvasConnectionManager.hpp"
#include "graph/StateDef.hpp"
#include "resource/SharedResource.hpp"

namespace ui
{
    class StateNodeHeader : public MyLabel<std::string>
    {
    public:
        explicit StateNodeHeader(StateNodeWidget& parent);
        void paint(juce::Graphics &g) override;
        void resized() override;
        void updateName();
        void mouseDown(const juce::MouseEvent &event) override;

    private:
        StateNodeWidget& parent;
        std::shared_ptr<std::string> name;
    };


    class StateNodeWidget : public juce::Component,
                            public juce::DragAndDropTarget,
                            public SelectionTarget,
                            public std::enable_shared_from_this<StateNodeWidget>
    {
        int headerHeight{15};
        bool selected{false};
        bool isCurrent{false};
        bool dragEnter{false};

        resource::Handle<sm::StateDef> state;

        juce::ComponentDragger dragger;

        std::shared_ptr<Component> propertyComponent;

        StateNodeHeader header;
        CanvasConnectionManager::Ptr &manager;

    public:
        using Ptr = std::shared_ptr<StateNodeWidget>;

        static Ptr create(const resource::Handle<sm::StateDef>& state, CanvasConnectionManager::Ptr &manager, juce::Point<int> pos)
        {
            auto ptr = std::make_shared<StateNodeWidget>(state, manager);
            ptr->setBounds(pos.x, pos.y, 150, 120);
            return ptr;
        }

        explicit StateNodeWidget(resource::Handle<sm::StateDef> state, CanvasConnectionManager::Ptr &connectionManager_);

        void paint(juce::Graphics &g) override;
        void resized() override;
        void setName(const juce::String &newName) override;

        void mouseDown(const juce::MouseEvent &event) override;
        void mouseDrag(const juce::MouseEvent &event) override;
        void mouseUp(const juce::MouseEvent &event) override;
        bool keyPressed(const juce::KeyPress &key) override;

        bool isInterestedInDragSource(const SourceDetails &dragSourceDetails) override;
        void itemDragEnter(const SourceDetails &dragSourceDetails) override;
        void itemDragExit(const SourceDetails &dragSourceDetails) override;
        void itemDropped(const SourceDetails &dragSourceDetails) override;

        resource::Handle<sm::StateDef>& getState();

        std::shared_ptr<Component> createConfig() override;

        void onSelect() override
        {
            selected = true;
            repaint();
            // grabKeyboardFocus();
        }

        void onDeselect() override
        {
            selected = false;
            repaint();
        }

        /// Set whether the state machine is currently on this state
        void setCurrent(const bool current)
        {
            isCurrent = current;
            repaint();
        }

        void rename();

    private:
        class ConnectionCreationBox : public Component
        {
            CanvasConnectionManager::Ptr manager;

        public:
            ConnectionCreationBox(StateNodeWidget& parent_, CanvasConnectionManager::Ptr manager);

            void paint(juce::Graphics &g) override;
            void mouseDown(const juce::MouseEvent &event) override;
            void mouseUp(const juce::MouseEvent &event) override;
            void mouseDrag(const juce::MouseEvent &event) override;

            [[nodiscard]] juce::Point<float> getCentrePos() const;

            StateNodeWidget& parent;
        };

        ConnectionCreationBox connectionBox;

        int getBorderW() const
        {
            if (isCurrent || selected)
                return 2;

            return 1;
        }

        juce::Colour getBorderCol() const
        {
            if (isCurrent)
                return juce::Colours::red;

            if (dragEnter)
                return juce::Colours::red;

            if (selected)
                return juce::Colours::darkblue;

            return juce::Colours::black;
        }
    };

}
