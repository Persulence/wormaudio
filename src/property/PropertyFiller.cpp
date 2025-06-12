#include "PropertyFiller.hpp"

namespace ui
{
    using namespace juce;

    struct PropertyFiller::Priv
    {
        static void updateSize(PropertyFiller& self)
        {
            float maxLabelWidth = 0;
            for (const auto& widget : self.children)
            {
                maxLabelWidth = std::max(maxLabelWidth, widget->getDesiredLabelWidth());
            }

            for (const auto& widget : self.children)
            {
                widget->setLabelWidth(maxLabelWidth);
            }
        }
    };

    void PropertyFiller::addInner(std::shared_ptr<PropertyWidget> property)
    {
        children.push_back(property);
        addAndMakeVisible(property.get());

        Priv::updateSize(*this);
        resized();
    }

    void PropertyFiller::addInner(std::shared_ptr<PropertyFiller> filler)
    {
        children.push_back(filler);
        addAndMakeVisible(filler.get());

        Priv::updateSize(*filler);
        resized();
    }

    void PropertyFiller::resized()
    {
        float yOff = 0;
        for (const auto& widget: children)
        {
            widget->setBounds(0, yOff, getWidth(), widget->getDesiredHeight());
            yOff += widget->getHeight();
        }
    }

    float PropertyFiller::getDesiredHeight() const
    {
        int h = 0;
        for (const auto& widget: children)
        {
            h += widget->getDesiredHeight();
        }

        return h;
    }

    void PropertyFiller::refresh(PropertyFiller *child)
    {
        // if (const auto found = std::ranges::find_if(children, [&child](auto& c){ return c.get() == child; }); found != children.end())
        // {
        // }

        removeAllChildren();
        children.clear();
        initProperties();
    }

    void PropertyFiller::onChanged(RefreshLevel level)
    {
        switch (level)
        {
            case SOFT:
                refresh();
            case HARD:
                // Since this is a component, we can cheat
                auto comp = getParentComponent();
                if (auto parent = dynamic_cast<PropertyFiller*>(comp))
                {
                    parent->refresh(this);
                }
                break;
        }
    }
}
