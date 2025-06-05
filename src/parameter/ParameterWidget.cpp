#include "ParameterWidget.hpp"

#include "editor/Editor.hpp"
#include "widget/SliderWidget.hpp"

namespace ui
{
    using namespace juce;
    using namespace parameter;

    template<typename Def>
    class ImplWidget : public Component
    {
    protected:
        Def& def;
        ParameterInstance& instance;

        ImplWidget(Def& def_, ParameterInstance& instance_):
            def(def_), instance(instance_)
        {

        }
    };

    class ContinuousWidget : public ImplWidget<ContinuousParameterDef>, SliderWidget::C::Listener
    {
    public:
        SliderWidget slider;

        ContinuousWidget(ContinuousParameterDef& def, ParameterInstance& instance):
            ImplWidget(def, instance)
        {
            addAndMakeVisible(slider);
            slider.setRange(def.min, def.max, 0);
            slider.setValue(instance.getValue(), false);
            slider.onChanged.setup(this, [this](double value){ this->instance.setValue(value); });
        }

        void resized() override
        {
            slider.setBounds(getLocalBounds());
        }
    };

    class DiscreteWidget : public ImplWidget<DiscreteParameterDef>
    {
        SliderWidget slider;

    public:
        explicit DiscreteWidget(DiscreteParameterDef& def_, ParameterInstance& instance):
            ImplWidget(def_, instance)
        {
            addAndMakeVisible(slider);
            slider.setRange(def.min, def.max, 1);
        }

        void resized() override
        {
            slider.setBounds(getLocalBounds());
        }
    };

    class EnumWidget : public ImplWidget<EnumParameterDef>
    {
    public:
        EnumWidget(EnumParameterDef& def_, ParameterInstance& instance):
            ImplWidget(def_, instance)
        {

        }
    };

    struct ParameterVisitor
    {
        ParameterInstance& instance;

        std::unique_ptr<Component> operator()(ContinuousParameterDef& def) const
        {
            return std::make_unique<ContinuousWidget>(def, instance);
        }

        std::unique_ptr<Component> operator()(DiscreteParameterDef& def) const
        {
            return std::make_unique<DiscreteWidget>(def, instance);
        }

        std::unique_ptr<Component> operator()(EnumParameterDef& def) const
        {
            return std::make_unique<EnumWidget>(def, instance);
        }
    };

    ParameterWidget::ParameterWidget(ParameterInstance &instance_):
        instance(instance_)
    {
        refresh();
        child->addMouseListener(this, true);

        label.setEditable(true);
        label.setText(String{instance.parameter->getName()}, NotificationType::dontSendNotification);
        label.onTextChange = [this]
        {
            editor::Editor::getInstance().getGlobalParameters().rename(instance.parameter, label.getText().toStdString());
        };
    }

    void ParameterWidget::refresh()
    {
        removeAllChildren();

        ParameterVisitor visitor{instance};
        child = std::visit(visitor, *instance.parameter);
        addAndMakeVisible(child.get());
        addAndMakeVisible(label);
    }

    void ParameterWidget::resized()
    {
        auto rect = getLocalBounds();
        label.setBounds(rect.removeFromTop(20));
        child->setBounds(rect);
    }

    void ParameterWidget::mouseDoubleClick(const MouseEvent &event)
    {

    }
}
