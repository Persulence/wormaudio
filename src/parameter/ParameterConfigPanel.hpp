// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <utility>

#include "editor/Editor.hpp"
#include "juce_gui_basics/juce_gui_basics.h"
#include "panel/MyPropertyPanel.hpp"
#include "signal/Signal.hpp"

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
            box.addItem("Continuous", ParameterType::CONTINUOUS + 1);
            box.addItem("Discrete", ParameterType::DISCRETE + 1);
            box.addItem("Enum", ParameterType::ENUM + 1);
            box.onChange = [this]
            {
                listener(ParameterType::get(box.getSelectedId() - 1));
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
        { }
    protected:

    public:
        void initProperties() override;
    };

    // Base class for ParameterDef properties
    template <class T>
    class BaseParameterDefFiller : public PropertyFiller
    {
    protected:
        using ValueEntry = EntryPropertyWidget<float>;

        T& def;

        explicit BaseParameterDefFiller(T& def_):
            def(def_) { }

        void initProperties() override
        {
            auto paramType = parameter::getType<T>();
            setHeader(std::make_unique<SectionHeader>("Parameter (" + paramType.name + ")"));

            add(std::make_shared<StringPropertyWidget>("Parameter name", def.name));

            const auto type = std::make_shared<ParameterTypePropertyWidget>("Type");
            add(type);
            type->setValue(paramType);
            type->listener = [this](parameter::ParameterType id)
            {
                using namespace parameter;
                auto& editor = editor::Editor::getInstance();

                if (auto parent = findParentComponentOfClass<ParameterProperties>())
                {
                    std::shared_ptr<ParameterDef> newParameter;

                    switch (id)
                    {
                        case ParameterType::CONTINUOUS:
                            newParameter = std::make_shared<ParameterDef>(ContinuousParameterDef{0, 1, def.getName()});
                            break;
                        case ParameterType::DISCRETE:
                            newParameter = std::make_shared<ParameterDef>(DiscreteParameterDef{0, 1, def.getName()});
                            break;
                        case ParameterType::ENUM:
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
