#pragma once
#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    class PropertyWidget : public juce::Component
    {
    public:
        // virtual ~PropertyWidget() = default;

        explicit PropertyWidget(std::string label);
        float getDesiredLabelWidth() const;
        void setLabelWidth(float labelWidth_);

        void resized() override;
        void paint(juce::Graphics &g) override;

    protected:
        virtual void setContentBounds(juce::Rectangle<int> bounds) = 0;

    private:
        std::string label;
        float labelWidth;

        juce::Label labelComponent;
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


    class MyPropertyPanel : public juce::Component
    {
    public:

        auto add(auto property) -> decltype(*property)&
        {
            addInner(property);
            return *property;
        }

        void resized() override;
        void paint(juce::Graphics &g) override;

    private:
        struct Priv;
        PropertyWidget &addInner(std::shared_ptr<PropertyWidget> property);
        std::vector<std::shared_ptr<PropertyWidget>> widgets;
    };
}
