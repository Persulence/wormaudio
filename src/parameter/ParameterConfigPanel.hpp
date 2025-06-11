#pragma once

#include <utility>

#include "editor/Editor.hpp"
#include "juce_gui_basics/juce_gui_basics.h"
#include "panel/MyPropertyPanel.hpp"
#include "signal/Signal.hpp"

import parameter;

namespace ui
{
    struct WrappedValue : juce::Value::Listener
    {
        juce::Value value;
        std::function<void(juce::Value&)> callback{};

        WrappedValue()
        {
            value.addListener(this);
        }

        void valueChanged(juce::Value &value) override
        {
            callback(value);
        }

        explicit operator juce::Value&()
        {
            return value;
        }
    };

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

    class ParameterConfig : public MyPropertyPanel
    {
    public:
        using ValueEntry = EntryPropertyWidget<float>;
        using OnChange = signal_event::Callback<>;
        OnChange::Signal onChange;

    protected:
        parameter::Parameter parameter;

        std::shared_ptr<EntryPropertyWidget<std::string>> name;
        std::shared_ptr<ParameterTypePropertyWidget> type;


        explicit ParameterConfig(parameter::Parameter parameter_):
            parameter(std::move(parameter_))
        {
            auto name = std::make_shared<EntryPropertyWidget<std::string>>("Parameter name", std::identity{}, std::identity{});
            add(name);
            name->setValue(parameter->getName());
            name->listener = [this, &name](const auto& val)
            {
                auto& editor = editor::Editor::getInstance();
                if (editor.getGlobalParameters().rename(parameter, val))
                {
                    onChange.emit();
                }
                else
                {
                    name->setValue(parameter->getName());
                }
            };

            type = std::make_shared<ParameterTypePropertyWidget>("Type");
            add(type);
            type->setValue(parameter->getType());
            type->listener = [this](parameter::ParameterType id)
            {
                using namespace parameter;
                auto& editor = editor::Editor::getInstance();

                std::shared_ptr<ParameterDef> newParameter;

                switch (id)
                {
                    case CONTINUOUS:
                        newParameter = std::make_shared<ParameterDef>(ContinuousParameterDef{0, 1, parameter->getName()});
                        break;
                    case DISCRETE:
                        newParameter = std::make_shared<ParameterDef>(DiscreteParameterDef{0, 1, parameter->getName()});
                        break;
                    case ENUM:
                        newParameter = std::make_shared<ParameterDef>(EnumParameterDef{parameter->getName()});
                        break;
                }

                if (editor.getGlobalParameters().changeType(parameter, newParameter))
                {
                    onChange.emit();
                }
            };
        }
    };

}
