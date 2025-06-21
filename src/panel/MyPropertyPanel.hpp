#pragma once

#include "property/PropertyFiller.hpp"

namespace ui
{
    class ValuePropertyWidget : public PropertyWidget
    {
    public:
        explicit ValuePropertyWidget(const std::string &label, const juce::Value &value):
            PropertyWidget(label)
        {
            addAndMakeVisible(field);
            field.setEditable(true);
            field.getTextValue().referTo(value);
        }

    protected:
        void setContentBounds(juce::Rectangle<int> bounds) override
        {
            field.setBounds(bounds);
        }

    private:
        juce::Label field;
    };

    class BoolPropertyWidget : public PropertyWidget
    {
    public:
        explicit BoolPropertyWidget(const std::string &label, juce::Value value_) :
            PropertyWidget(label), value(std::move(value_))
        {
            addAndMakeVisible(button);
            button.getToggleStateValue().referTo(value);
        }

    protected:
        void setContentBounds(juce::Rectangle<int> bounds) override
        {
            button.setBounds(bounds);
        }

    private:
        juce::ToggleButton button;
        juce::Value value;
    };

    template<typename Value>
    class EntryPropertyWidget : public PropertyWidget
    {
    public:
        // using Value = float; // TODO convert to template
        using Listener = std::function<void(Value)>;
        using Parse = std::function<Value(std::string)>;
        using ToString = std::function<std::string(Value)>;

        Listener listener{};
        ToString toString;

        explicit EntryPropertyWidget(const std::string &label, Parse parse_, ToString toString = [](const Value v){ return std::to_string(v); }):
            PropertyWidget(label), parse(std::move(parse_)), toString(std::move(toString))
        {
            addAndMakeVisible(content);
            content.setEditable(true);

            content.onTextChange = [this]
            {
                const std::string text = content.getText().toStdString();
                const Value val = parse(text);
                listener(val);
            };
        }

        void setValue(Value val)
        {
            content.setText(juce::String{toString(val)}, juce::dontSendNotification);
        }

    protected:
        void setContentBounds(const juce::Rectangle<int> bounds) override
        {
            content.setBounds(bounds);
        }

    private:
        juce::Label content;
        Parse parse;
    };
}
