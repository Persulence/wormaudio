#include "ParameterWidget.hpp"

#include <utility>

#include "ContinuousParameterConfig.hpp"
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
        ComboBox box;

    public:
        EnumWidget(EnumParameterDef& def_, ParameterInstance& instance):
            ImplWidget(def_, instance)
        {
            addAndMakeVisible(box);

            int i = 1;
            for (auto& [name, value] : def.values)
            {
                box.addItem(name, i);
                i++;
            }

            box.setSelectedId(instance.getValue() + 1);
            box.onChange = [this](){ this->instance.setValue(box.getSelectedId() - 1); };
        }

        void paint(Graphics &g) override
        {
            const auto bounds = getLocalBounds().toFloat().expanded(-0.5f);
            g.setColour(Colours::black);
            g.drawRoundedRectangle(bounds, 5, 1);
        }

        void resized() override
        {
            box.setBounds(getLocalBounds());
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

    ParameterWidget::ParameterWidget(sm::ParameterLookup &lookup_, Parameter parameter_):
        lookup(lookup_), parameter(std::move(parameter_))
    {
        refresh();
        label.addMouseListener(this, true);

        label.setEditable(true);
        label.setText(String{parameter->getName()}, dontSendNotification);
        label.onTextChange = [this]
        {
            auto& editor = editor::Editor::getInstance();

            if (!editor.getGlobalParameters().rename(parameter, label.getText().toStdString()))
            {
                // Return to previous name
                label.setText(parameter->getName(), dontSendNotification);
            }
            refresh();
        };
    }

    void ParameterWidget::refresh()
    {
        removeAllChildren();

        ParameterVisitor visitor{getParameter()};
        child = std::visit(visitor, *parameter);
        addAndMakeVisible(child.get());
        addAndMakeVisible(label);
        resized();
    }

    void ParameterWidget::resized()
    {
        auto rect = getLocalBounds();
        label.setBounds(rect.removeFromTop(20));
        child->setBounds(rect);
    }

    void ParameterWidget::mouseDown(const MouseEvent &event)
    {
        if (event.mods.isRightButtonDown())
        {
            PopupMenu menu;
            menu.addItem("Edit", [this]
            {
                auto visitor = ConfigComponentVisitor{};
                auto leak = std::visit(visitor, *parameter);
                leak->onChange.setup(this, [this]{ refresh(); });

                DialogWindow::LaunchOptions o;
                o.content.setOwned(leak.release());
                o.resizable = false;
                o.content->setBounds(Rectangle{0, 0, 500, 500});
                o.dialogBackgroundColour = Colours::grey;
                o.launchAsync();
            });
            menu.showMenuAsync(PopupMenu::Options{});
        }
    }

    ParameterInstance &ParameterWidget::getParameter() const
    {
        return lookup.get(parameter);
    }
}
