#pragma once

#include "StateNodeWidget.fwd.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

#include "CanvasSelectionManager.hpp"
#include "CanvasConnectionManager.hpp"
#include "graph/StateDef.hpp"
#include "resource/SharedResource.hpp"

namespace ui
{
    class StateNodeHeader : public juce::Label
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
        int borderWidth{1};
        bool selected{false};
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
            borderWidth = 2;
            repaint();
            // grabKeyboardFocus();
        }

        void onDeselect() override
        {
            selected = false;
            borderWidth = 1;
            repaint();
        }

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
