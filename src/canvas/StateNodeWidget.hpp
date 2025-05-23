#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "StateConnectionManager.hpp"

namespace ui
{
    class StateNodeHeader : public juce::Label
    {
    public:
        StateNodeHeader();
        void paint(juce::Graphics &g) override;
        void resized() override;
        void mouseDown(const juce::MouseEvent &event) override;

    private:
        std::shared_ptr<std::string> name;
    };


    class ConnectionCreationBox : public juce::Component
    {
        StateConnectionManager::Ptr manager;

    public:
        explicit ConnectionCreationBox(const StateConnectionManager::Ptr& manager);

        void paint(juce::Graphics &g) override;
        void mouseDown(const juce::MouseEvent &event) override;
        void mouseUp(const juce::MouseEvent &event) override;
        void mouseDrag(const juce::MouseEvent &event) override;

        [[nodiscard]] juce::Point<float> getCentrePos() const;

    };


    class StateNodeWidget : public juce::Component
    {
        int headerHeight{15};
        int borderWidth{1};

        juce::ComponentDragger dragger;
        // StateConnectionManager::Ptr connectionManager;

    public:
        using Ptr = std::shared_ptr<StateNodeWidget>;

        static Ptr create(const StateConnectionManager::Ptr& manager, juce::Point<int> pos);
        explicit StateNodeWidget(const StateConnectionManager::Ptr &connectionManager_);

        void paint(juce::Graphics &g) override;
        void resized() override;

        void mouseDown(const juce::MouseEvent &event) override;
        void mouseDrag(const juce::MouseEvent &event) override;
        void mouseUp(const juce::MouseEvent &event) override;


    private:
        StateNodeHeader header;
        ConnectionCreationBox connectionBox;
    };

}
