#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "CanvasSelectionManager.hpp"
#include "CanvasConnectionManager.hpp"

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
        juce::Colour defaultBorderCol{juce::Colours::black};

        juce::ComponentDragger dragger;
        sm::State::Ptr state;

        std::shared_ptr<Component> propertyComponent;

    public:
        using Ptr = std::shared_ptr<StateNodeWidget>;

        static Ptr create(const sm::State::Ptr& state, CanvasConnectionManager::Ptr &manager, juce::Point<int> pos)
        {
            auto ptr = std::make_shared<StateNodeWidget>(state, manager);
            ptr->setBounds(pos.x, pos.y, 150, 120);
            return ptr;
        }

        explicit StateNodeWidget(sm::State::Ptr state, CanvasConnectionManager::Ptr &connectionManager_);

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

        std::shared_ptr<Component> createConfig() override
        {
            if (propertyComponent == nullptr)
            {
                const auto ptr = std::make_shared<juce::TextButton>();
                ptr->setButtonText(state->name);

                propertyComponent = ptr;
            }
            return propertyComponent;
        }

        void onSelect() override
        {
            selected = true;
            borderWidth = 2;
            repaint();
        }

        void onDeselect() override
        {
            selected = false;
            borderWidth = 1;
            repaint();
        }

    private:
        class ConnectionCreationBox : public juce::Component
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

        StateNodeHeader header;
        ConnectionCreationBox connectionBox;
        CanvasConnectionManager::Ptr &manager;
        bool selected{false};
        bool dragEnter{false};

        juce::Colour getBorderCol() const
        {
            if (dragEnter)
                return juce::Colours::red;

            if (selected)
                return juce::Colours::white;

            return juce::Colours::black;
        }
    };

}
