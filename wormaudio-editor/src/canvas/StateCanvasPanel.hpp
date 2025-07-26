// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <editor/EditorState.hpp>

#include "StateNodeWidget.hpp"
#include "canvas/CanvasConnectionManager.hpp"
#include "../panel/Panel.hpp"

#include "editor/Editor.fwd.hpp"

namespace sm
{
    class StateMachineDefinition;
}

namespace ui
{
    class StateNodeWidget;

    class StateCanvasPanel : public Panel, public SimpleCommandTarget
    {
        std::vector<std::shared_ptr<StateNodeWidget>> stateNodes;
        std::unordered_map<std::shared_ptr<sm::StateDef>, std::shared_ptr<StateNodeWidget>> stateToNode;
        CanvasConnectionManager::Ptr connectionManager{};

        // TODO: temporary
        resource::Handle<event::EventDef> currentEvent;

        sm::OnStateChange::Listener stateChangeListener;

        std::shared_ptr<StateNodeWidget> currentState;

        editor::EventChanged::Listener eventChangedListener;
        editor::BeforeEditorStateSave::Listener beforeSaveListener;

    public:
        StateCanvasPanel();

        StateNodeWidget::Ptr addNode(const std::shared_ptr<StateNodeWidget> &node);

        /// Creates a new state and adds a corresponding node
        StateNodeWidget::Ptr addState(juce::Point<int> pos);
        void removeNode(const std::shared_ptr<StateNodeWidget> &node);
        void paint(juce::Graphics &g) override;
        void resized() override;
        bool keyPressed(const juce::KeyPress &key) override;

        void updateCanvas(const StateNodeWidget::Ptr& node);

        void contextMenu(juce::Point<int> mousePos);

        juce::Rectangle<int> calculateBounds() const;

        void removeSelectedNode();

        void renameSelectedNode() const;

    private:
        void fillNodes();
        editor::SoundCanvasData saveNodePositions() const;
        void readNodePositions(const editor::SoundCanvasData& data) const;
    };
}
