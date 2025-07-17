// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once
#include "property/PropertyWidget.hpp"
#include "util/Data.hpp"

namespace ui
{
    template <typename T>
    class ChoicePropertyWidget : public PropertyWidget
    {
    public:
        struct Entry
        {
            std::string name;
            T value;
        };

        static std::unique_ptr<ChoicePropertyWidget> create(std::string name, std::vector<Entry> values, T* target)
        {
            return std::make_unique<ChoicePropertyWidget>(name, values, target);
        }

        std::function<void()> onChange{[]{}};

        explicit ChoicePropertyWidget(const std::string &label, const std::vector<Entry> &values_, T* target_);

    protected:
        void setContentBounds(juce::Rectangle<int> bounds) override;

        std::vector<Entry> values;

    private:
        juce::ComboBox comboBox;
        // util::Data<Type> data;
        // util::Data<Type>::Listener listener;
        T * target;
    };

    template <typename T>
    ChoicePropertyWidget<T>::ChoicePropertyWidget(const std::string &label, const std::vector<Entry> &values_, T* target_):
        PropertyWidget(label), values(values_), target(target_)
    {
        addAndMakeVisible(comboBox);
        comboBox.onChange = [this]
        {
            // data.setValue(comboBox.getSelectedId() - 1);
            *target = values.at(comboBox.getSelectedId() - 1).value;
            onChange();
        };
        // data.setupListener(&listener, [this](auto& val)
        // {
        //     comboBox.setSelectedId(val + 1);
        // });

        // for (const auto&[name, value] : values)
        for (int i = 0; i < values.size(); ++i)
        {
            auto& entry = values.at(i);
            comboBox.addItem(entry.name, i + 1);
        }

        comboBox.setEditableText(false);
        int idx = std::find_if(values.begin(), values.end(), [this](auto& e){return e.value == *target; }) - values.begin();
        comboBox.setSelectedId(idx + 1);
    }

    template <typename T>
    void ChoicePropertyWidget<T>::setContentBounds(const juce::Rectangle<int> bounds)
    {
        comboBox.setBounds(bounds);
    }
}
