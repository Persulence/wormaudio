#include "MyPropertyPanel.hpp"

namespace ui
{
    using namespace juce;

    PropertyWidget::PropertyWidget(std::string label_):
        label(label_)
    {
        labelWidth = getDesiredLabelWidth();

        addAndMakeVisible(labelComponent);
        labelComponent.setText(label, dontSendNotification);
    }

    float PropertyWidget::getDesiredLabelWidth() const
    {
        return labelComponent.getFont().getStringWidth(label) * 1.1;
    }

    void PropertyWidget::setLabelWidth(float labelWidth_)
    {
        labelWidth = labelWidth_;
    }

    void PropertyWidget::resized()
    {
        // labelComponent.setBounds(0, 0, labelWidth, getHeight());
        auto rect = getLocalBounds();
        labelComponent.setBounds(rect.removeFromLeft(labelWidth));

        // Padding?

        setContentBounds(rect);
    }

    void PropertyWidget::paint(Graphics &g)
    {
        float thickness = 1;
        const auto bounds = getLocalBounds().toFloat().expanded(-thickness / 2);
        g.setColour(Colours::black);
        g.drawRoundedRectangle(bounds, 5, thickness);
        g.drawVerticalLine(labelWidth, 0, getHeight());
    }


    struct MyPropertyPanel::Priv
    {
        static void updateSize(MyPropertyPanel& self)
        {
            float maxLabelWidth = 0;
            for (const auto& widget : self.widgets)
            {
                maxLabelWidth = std::max(maxLabelWidth, widget->getDesiredLabelWidth());
            }

            for (const auto& widget : self.widgets)
            {
                widget->setLabelWidth(maxLabelWidth);
            }
        }
    };

    PropertyWidget &MyPropertyPanel::addInner(std::shared_ptr<PropertyWidget> property)
    {
        widgets.push_back(property);
        addAndMakeVisible(property.get());

        Priv::updateSize(*this);
        resized();

        return *property;
    }

    void MyPropertyPanel::resized()
    {
        float elementH = 30;

        float yOff = 0;
        for (const auto& widget: widgets)
        {
            widget->setBounds(0, yOff, getWidth(), elementH);
            yOff += widget->getHeight();
        }
    }

    void MyPropertyPanel::paint(Graphics &g)
    {
        // g.fillRect(getLocalBounds());
    }
}
