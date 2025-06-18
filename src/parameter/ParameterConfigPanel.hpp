#pragma once

#include <utility>

#include "editor/Editor.hpp"
#include "juce_gui_basics/juce_gui_basics.h"
#include "panel/MyPropertyPanel.hpp"
#include "signal/Signal.hpp"

import parameter;

namespace ui
{
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

        parameter::Parameter parameter;

        explicit ParameterProperties(parameter::Parameter parameter_):
            parameter(std::move(parameter_))
        {
            ParameterProperties::initProperties();
        }

    protected:

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
            name->setValue(def.getName());
            name->listener = [this, &name](const auto& val)
            {
                // TODO
                if (auto parent = findParentComponentOfClass<ParameterProperties>())
                {
                    auto parameter = parent->parameter;
                    auto& editor = editor::Editor::getInstance();
                    if (editor.getEditorParameters().rename(parameter, val))
                    {
                        onChanged(SOFT);
                    }
                    else
                    {
                        name->setValue(parameter->getName());
                    }
                }
            };

            type = std::make_shared<ParameterTypePropertyWidget>("Type");
            add(type);
            type->setValue(parameter::getType<T>());
            type->listener = [this](parameter::ParameterType id)
            {
                using namespace parameter;
                auto& editor = editor::Editor::getInstance();

                if (auto parent = findParentComponentOfClass<ParameterProperties>())
                {
                    std::shared_ptr<ParameterDef> newParameter;

                    switch (id)
                    {
                        case CONTINUOUS:
                            newParameter = std::make_shared<ParameterDef>(ContinuousParameterDef{0, 1, def.getName()});
                            break;
                        case DISCRETE:
                            newParameter = std::make_shared<ParameterDef>(DiscreteParameterDef{0, 1, def.getName()});
                            break;
                        case ENUM:
                            newParameter = std::make_shared<ParameterDef>(EnumParameterDef{def.getName()});
                            break;
                    }

                    if (editor.getEditorParameters().changeType(parent->parameter, newParameter))
                    {
                        onChanged(HARD);
                    }
                }
            };
        }
    };

}
