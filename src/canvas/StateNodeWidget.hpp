#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "CanvasSelectionManager.hpp"
#include "StateConnectionManager.hpp"

import control;

namespace ui
{
    class StateNodeWidget;

    class StateNodeHeader : public juce::Label
    {
    public:
        explicit StateNodeHeader(StateNodeWidget& parent);
        void paint(juce::Graphics &g) override;
        void resized() override;
        void mouseDown(const juce::MouseEvent &event) override;

    private:
        StateNodeWidget& parent;
        std::shared_ptr<std::string> name;
    };


    class StateNodeWidget : public juce::Component,
                            public juce::DragAndDropTarget,
                            public CanvasSelectionTarget,
                            public std::enable_shared_from_this<StateNodeWidget>
    {
        int headerHeight{15};

        int borderWidth{1};
        juce::Colour borderCol{juce::Colours::black};

        juce::ComponentDragger dragger;
        sm::State::Ptr state;

    public:
        using Ptr = std::shared_ptr<StateNodeWidget>;

        static Ptr create(const sm::State::Ptr& state, StateConnectionManager::Ptr &manager, juce::Point<int> pos)
        {
            auto ptr = std::make_shared<StateNodeWidget>(state, manager);
            ptr->setBounds(pos.x, pos.y, 150, 120);
            return ptr;
        }

        explicit StateNodeWidget(sm::State::Ptr state, StateConnectionManager::Ptr &connectionManager_);

        void paint(juce::Graphics &g) override;
        void resized() override;

        void mouseDown(const juce::MouseEvent &event) override;
        void mouseDrag(const juce::MouseEvent &event) override;
        void mouseUp(const juce::MouseEvent &event) override;

        bool isInterestedInDragSource(const SourceDetails &dragSourceDetails) override;
        void itemDragEnter(const SourceDetails &dragSourceDetails) override;
        void itemDragExit(const SourceDetails &dragSourceDetails) override;
        void itemDropped(const SourceDetails &dragSourceDetails) override;

        sm::State::Ptr& getState();

        std::unique_ptr<Component> createConfig() override
        {
            auto ptr = std::make_unique<juce::TextButton>();
            ptr->setButtonText(state->name);
            return ptr;
        }

    private:
        class ConnectionCreationBox : public juce::Component
        {
            StateConnectionManager::Ptr manager;

        public:
            ConnectionCreationBox(StateNodeWidget& parent_, StateConnectionManager::Ptr manager);

            void paint(juce::Graphics &g) override;
            void mouseDown(const juce::MouseEvent &event) override;
            void mouseUp(const juce::MouseEvent &event) override;
            void mouseDrag(const juce::MouseEvent &event) override;

            [[nodiscard]] juce::Point<float> getCentrePos() const;

            StateNodeWidget& parent;
        };

        StateNodeHeader header;
        ConnectionCreationBox connectionBox;
        StateConnectionManager::Ptr &manager;
    };

}
