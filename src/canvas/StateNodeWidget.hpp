#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace ui
{
    class StateNodeHeader : public juce::Label
    {
    public:
        StateNodeHeader();

    private:
        std::shared_ptr<std::string> name;
    };

    class StateNodeWidget : public juce::Component
    {
        int headerHeight{10};

        juce::ComponentDragger dragger;

    public:
        using Ptr = std::shared_ptr<StateNodeWidget>;

        static Ptr create(juce::Point<int> pos);
        StateNodeWidget();

        void paint(juce::Graphics &g) override;
        void resized() override;

        void mouseDown(const juce::MouseEvent &event) override;
        void mouseDrag(const juce::MouseEvent &event) override;
        void mouseUp(const juce::MouseEvent &event) override;


    private:
        StateNodeHeader header;
    };

}
