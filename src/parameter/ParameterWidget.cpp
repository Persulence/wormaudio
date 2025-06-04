#include "ParameterWidget.hpp"

#include "widget/SliderWidget.hpp"

namespace ui
{
    using namespace juce;
    using namespace parameter;

    class ContinuousWidget : public Component
    {
    public:
        ContinuousParameterDef& def;
        SliderWidget slider;

        explicit ContinuousWidget(ContinuousParameterDef& def_):
            def(def_)
        {
            addAndMakeVisible(slider);
            slider.setRange(def.min, def.max, 0);
        }

        void resized() override
        {
            slider.setBounds(getLocalBounds());
        }
    };

    class DiscreteWidget : public Component
    {
        DiscreteParameterDef& def;
        SliderWidget slider;

    public:
        explicit DiscreteWidget(DiscreteParameterDef& def_):
            def(def_)
        {
            addAndMakeVisible(slider);
            slider.setRange(def.min, def.max, 1);
        }

        void resized() override
        {
            slider.setBounds(getLocalBounds());
        }
    };

    class EnumWidget : public Component
    {
    public:
        EnumParameterDef& def;

        explicit EnumWidget(EnumParameterDef& def_):
            def(def_)
        {

        }
    };

    struct ParameterVisitor
    {
        std::unique_ptr<Component> operator()(ContinuousParameterDef& def) const
        {
            return std::make_unique<ContinuousWidget>(def);
        }

        std::unique_ptr<Component> operator()(DiscreteParameterDef& def) const
        {
            return std::make_unique<DiscreteWidget>(def);
        }

        std::unique_ptr<Component> operator()(EnumParameterDef& def) const
        {
            return std::make_unique<EnumWidget>(def);
        }
    };

    ParameterWidget::ParameterWidget(ParameterInstance &instance_):
        instance(instance_)
    {
        refresh();
    }

    void ParameterWidget::refresh()
    {
        removeAllChildren();
        child = std::visit(ParameterVisitor{}, *instance.parameter);
        addAndMakeVisible(child.get());
    }

    void ParameterWidget::resized()
    {
        child->setBounds(getLocalBounds());
    }
}
