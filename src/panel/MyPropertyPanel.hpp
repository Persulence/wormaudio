#pragma once

#include "property/PropertyFiller.hpp"

namespace ui
{
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
