#pragma once

#include <utility>

#include "editor/Editor.hpp"
#include "juce_gui_basics/juce_gui_basics.h"
#include "panel/MyPropertyPanel.hpp"
#include "signal/Signal.hpp"

import parameter;

namespace ui
{
    // struct WrappedValue : juce::Value::Listener
    // {
    //     juce::Value value;
    //     std::function<void(juce::Value&)> callback{};
    //
    //     WrappedValue()
    //     {
    //         value.addListener(this);
    //     }
    //
    //     void valueChanged(juce::Value &value) override
    //     {
    //         callback(value);
    //     }
    //
    //     explicit operator juce::Value&()
    //     {
    //         return value;
    //     }
    // };

    class ParameterTypePropertyWidget : public PropertyWidget
    {
    public:
        std::function<void(parameter::ParameterType)> listener;

        explicit ParameterTypePropertyWidget(const std::string &label) :
            PropertyWidget(label)
        {
            using namespace parameter;

            // Argh
            box.addItem("Continuous", CONTINUOUS + 1);
            box.addItem("Discrete", DISCRETE + 1);
            box.addItem("Enum", ENUM + 1);
            box.onChange = [this]
            {
                listener(static_cast<ParameterType>(box.getSelectedId() - 1));
            };

            addAndMakeVisible(box);
        }

        void setValue(const parameter::ParameterType type)
        {
            box.setSelectedId(type + 1, juce::dontSendNotification);
            repaint();
        }

    protected:
        void setContentBounds(const juce::Rectangle<int> bounds) override
        {
            box.setBounds(bounds);
        }

    private:
        juce::ComboBox box;
    };

    // Property object for Parameter
    class ParameterProperties : public PropertyFiller
    {
    public:
        using OnChange = signal_event::Callback<>;
        OnChange::Signal onChange;

        explicit ParameterProperties(parameter::Parameter parameter_):
            parameter(std::move(parameter_))
        {
            ParameterProperties::initProperties();
        }

    protected:
        parameter::Parameter parameter;

    public:
        void initProperties() override;
    };

    // Base class for ParameterDef properties
    template <class T>
    class BaseParameterDefProperties : public PropertyFiller
    {
        std::shared_ptr<EntryPropertyWidget<std::string>> name;
        std::shared_ptr<ParameterTypePropertyWidget> type;

    protected:
        using ValueEntry = EntryPropertyWidget<float>;

        T& def;

        explicit BaseParameterDefProperties(T& def_):
            def(def_)
        {
            auto name = std::make_shared<EntryPropertyWidget<std::string>>("Parameter name", std::identity{}, std::identity{});
            add(name);
            name->setValue(def.name);
            name->listener = [this, &name](const auto& val)
            {
                // TODO
                // auto& editor = editor::Editor::getInstance();
                // if (editor.getGlobalParameters().rename(parameter, val))
                // {
                //     onChange.emit();
                // }
                // else
                // {
                //     name->setValue(parameter->getName());
                // }
                onChanged(SOFT);
            };

            type = std::make_shared<ParameterTypePropertyWidget>("Type");
            add(type);
            type->setValue(parameter::getType<T>());
            type->listener = [this](parameter::ParameterType id)
            {
                using namespace parameter;
                auto& editor = editor::Editor::getInstance();

                std::shared_ptr<ParameterDef> newParameter;

                switch (id)
                {
                    case CONTINUOUS:
                        newParameter = std::make_shared<ParameterDef>(ContinuousParameterDef{0, 1, def.name});
                        break;
                    case DISCRETE:
                        newParameter = std::make_shared<ParameterDef>(DiscreteParameterDef{0, 1, def.name});
                        break;
                    case ENUM:
                        newParameter = std::make_shared<ParameterDef>(EnumParameterDef{def.name});
                        break;
                }

                // TODO
                // if (editor.getGlobalParameters().changeType(parameter, newParameter))
                // {
                //     onChange.emit();
                // }

                onChanged(HARD);
            };
        }
    };

}
