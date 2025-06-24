#include "ParameterWidget.hpp"

#include <utility>

#include "juce_gui_basics/juce_gui_basics.h"

#include "editor/Editor.hpp"
#include "../../player/src/util/WrappedValue.hpp"
#include "canvas/InspectorSelectionManager.hpp"
#include "inspector/InspectorRoot.hpp"
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
        WrappedValue min;
        WrappedValue max;

        ContinuousWidget(ContinuousParameterDef& def_, ParameterInstance& instance_):
            ImplWidget(def_, instance_)
        {
            auto rangeCallback = [this](auto&)
            {
                slider.setRange(def.min.getValue(), def.max.getValue(), 0);
                slider.setValue(instance.getValue(), false);
                repaint();
            };

            max.callback = rangeCallback;
            min.callback = rangeCallback;

            min.value.referTo(def.min);
            max.value.referTo(def.max);

            addAndMakeVisible(slider);
            slider.onChanged.setup(this, [this](const double value)
            {
                this->instance.setValue(static_cast<ParameterValue>(value));
            });
        }

        void resized() override
        {
            slider.setBounds(getLocalBounds());
        }
    };

    class DiscreteWidget : public ImplWidget<DiscreteParameterDef>, SliderWidget::C::Listener
    {
        SliderWidget slider;

        WrappedValue min;
        WrappedValue max;

    public:
        explicit DiscreteWidget(DiscreteParameterDef& def_, ParameterInstance& instance_):
            ImplWidget(def_, instance_)
        {
            auto rangeCallback = [this](auto&)
            {
                slider.setRange(def.min.getValue(), def.max.getValue(), 1);
                slider.setValue(instance.getValue(), false);
                repaint();
            };
            max.callback = rangeCallback;
            min.callback = rangeCallback;
            min.value.referTo(def.min);
            max.value.referTo(def.max);

            addAndMakeVisible(slider);
            slider.onChanged.setup(this, [this](double value)
            {
                this->instance.setValue(value);
            });
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

        label.setEditable(false, true, true);
        label.setData(parameter->getNameAsValue());
        // label.setText(String{parameter->getName()}, dontSendNotification);
        // label.onTextChange = [this]
        // {
        //     auto& editor = editor::Editor::getInstance();
        //
        //     if (!editor.getEditorParameters().rename(parameter, label.getText().toStdString()))
        //     {
        //         // Return to previous name
        //         label.setText(parameter->getName(), dontSendNotification);
        //     }
        //
        //     // Here lies an unfortunate conundrum. The above function may cause this object to be freed, which results in undefined behaviour when we call refresh.
        //     // This could be mitigated by better design, but I don't know how to design it better.
        //     // refresh();
        // };
    }

    void ParameterWidget::refresh()
    {
        removeAllChildren();

        ParameterVisitor visitor{getParameter()};
        child = std::visit(visitor, *parameter);
        label.setText(parameter->getName(), dontSendNotification);
        addAndMakeVisible(child.get());
        addAndMakeVisible(label);
        resized();

        child->addMouseListener(this, true);
    }

    void ParameterWidget::resized()
    {
        auto rect = getLocalBounds();
        label.setBounds(rect.removeFromTop(20));
        child->setBounds(rect);
    }

    void ParameterWidget::mouseDown(const MouseEvent &event)
    {
        if (auto manager = findParentComponentOfClass<InspectorSelectionManager>())
        {
            manager->select(shared_from_this());
        }

        // if (event.mods.isRightButtonDown())
        // {
        //     // c = std::make_unique<FileChooser>("thing", File{}, "*", false);
        //     // c->launchAsync(FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles, [](auto& fc){});
        //
        //     PopupMenu menu;
        //     menu.addItem("Edit", [this]
        //     {
        //         auto visitor = ConfigComponentVisitor{};
        //         auto leak = std::visit(visitor, *parameter);
        //         leak->onChange.setup(this, [this]{ refresh(); });
        //
        //         DialogWindow::LaunchOptions o;
        //         o.content.setOwned(leak.release());
        //         o.resizable = false;
        //         o.content->setBounds(Rectangle{0, 0, 500, 500});
        //         o.dialogBackgroundColour = Colours::grey;
        //         o.escapeKeyTriggersCloseButton = true;
        //
        //         DialogWindow *window = o.create();
        //         // auto handle = reinterpret_cast<Window>(window->getWindowHandle());
        //         // auto display = XWindowSystem::getInstance()->getDisplay();
        //         // auto atoms = XWindowSystemUtilities::Atoms{display};
        //         // XWindowSystemUtilities::GetXProperty get{display, handle, atoms.pid,
        //         //               0L,
        //         //               std::numeric_limits<long>::max(),
        //         //               false,
        //         //     atoms.pid
        //         // };
        //         //
        //         // std::cout << get.success << "\n";
        //         // std::cout << "data: " << get.data << "\n";
        //
        //         window->enterModalState(true, nullptr, true);
        //
        //     });
        //     menu.showMenuAsync(PopupMenu::Options{});
        // }
    }

    ParameterInstance &ParameterWidget::getParameter() const
    {
        return lookup.get(parameter);
    }

    std::shared_ptr<Component> ParameterWidget::createConfig()
    {
        return InspectorRoot::wrap(std::make_unique<ParameterProperties>(parameter));
    }
}
