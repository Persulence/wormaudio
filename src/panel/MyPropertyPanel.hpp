#pragma once

#include "property/PropertyFiller.hpp"
#include "util/Data.hpp"
#include "util/component/MyLabel.hpp"
#include "util/component/MyToggleButton.hpp"

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

    template<typename T>
    class DataPropertyWidget : public PropertyWidget
    {
    protected:
        DataPropertyWidget(const std::string& label, util::Data<T> data_):
            PropertyWidget(label), data(data_) {}

        void setContentBounds(juce::Rectangle<int> bounds) override
        {

        }

        util::Data<T> data;
    };

    class StringPropertyWidget : public PropertyWidget
    {
    public:
        MyLabel<std::string> field;

        explicit StringPropertyWidget(const std::string& label, const util::Data<std::string> &data_):
            PropertyWidget(label), data(data_)
        {
            addAndMakeVisible(field);
            field.setEditable(true);
            field.setData(data);
        }

    protected:
        void setContentBounds(juce::Rectangle<int> bounds) override
        {
            field.setBounds(bounds);
        }

        util::Data<std::string> data;
    };

    class BoolDataPropertyWidget : public PropertyWidget
    {
    public:
        explicit BoolDataPropertyWidget(const std::string &label, util::Data<bool> data) :
            PropertyWidget(label)
        {
            addAndMakeVisible(button);
            button.setData(data);
        }

    protected:
        void setContentBounds(juce::Rectangle<int> bounds) override
        {
            button.setBounds(bounds);
        }

    private:
        MyToggleButton button;
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
    class DataEntryPropertyWidget : public PropertyWidget
    {
    public:
        explicit DataEntryPropertyWidget(const std::string &label, util::Data<Value> data,
                                         typename MyLabel<Value>::Parse parse = [](const auto& s){ return s; }, typename MyLabel<Value>::ToString toString = parse::defaultToString<Value>):
            PropertyWidget(label), content(parse, toString)
        {
            addAndMakeVisible(content);
            content.setEditable(true);

            content.setData(data);
        }

    protected:
        void setContentBounds(const juce::Rectangle<int> bounds) override
        {
            content.setBounds(bounds);
        }

    private:
        MyLabel<Value> content;
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

        explicit EntryPropertyWidget(const std::string &label, Parse parse_, ToString toString = parse::defaultToString<Value>):
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
