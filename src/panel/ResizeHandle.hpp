#pragma once

#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    class ResizeHandle : public juce::Component
    {
    public:
        using Callback = std::function<void(float)>;
        enum class Direction;

    private:
        Direction direction;
        float width;
        float position;
        float margin;

    public:
        std::vector<Callback> drag;
        std::vector<Callback> commit;

        float currentPosition;

        explicit ResizeHandle(Direction direction_, float position, float width = 10, float margin = 20);
        void mouseDrag(const juce::MouseEvent &event) override;
        void mouseUp(const juce::MouseEvent &event) override;
        void paint(juce::Graphics &g) override;
        void resized() override;

        juce::FlexItem asFlexItem();

        enum class Direction
        {
            HORIZONTAL,
            VERTICAL
        };

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ResizeHandle)
    };

    template <typename T>
    T choose(ResizeHandle::Direction direction, T hor, T ver)
    {
        switch (direction)
        {
            case ResizeHandle::Direction::VERTICAL:
            {
                return ver;
            }
            case ResizeHandle::Direction::HORIZONTAL:
            {
                return hor;
            }
        }
    }
}