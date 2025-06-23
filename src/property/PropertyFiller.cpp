#include "PropertyFiller.hpp"

namespace ui
{
    using namespace juce;

    /// --- SectionHeader ---

    PropertyFiller::SectionHeader::SectionHeader(const std::string &name_)
    {
        setText(name_, dontSendNotification);
        setFont(
            getFont().withStyle(Font::bold)
        );
    }

    void PropertyFiller::SectionHeader::paint(Graphics &g)
    {
        g.setColour(Colours::darkblue);
        g.fillRect(getLocalBounds());

        Label::paint(g);
    }

    /// --- PropertyFiller ---

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

    void PropertyFiller::addInner(const std::shared_ptr<PropertyMember> &member)
    {
        if (const auto filler = std::dynamic_pointer_cast<PropertyFiller>(member))
            filler->initProperties();

        children.push_back(member);
        addAndMakeVisible(member.get());

        Priv::updateSize(*this);
        resized();
    }

    // void PropertyFiller::addInner(const std::shared_ptr<PropertyFiller>& filler)
    // {
    //     filler->initProperties();
    //
    //     children.push_back(filler);
    //     addAndMakeVisible(filler.get());
    //
    //     Priv::updateSize(*filler);
    //     resized();
    // }

    void PropertyFiller::resized()
    {
        int yOff = 0;

        if (header)
        {
            header->setBounds(0, yOff, getWidth(), header->h);
            yOff += header->h;
        }

        for (const auto& widget: children)
        {
            widget->setBounds(0, yOff, getWidth(), widget->getDesiredHeight());
            yOff += widget->getHeight();
        }
    }

    int PropertyFiller::getDesiredHeight() const
    {
        int h = 0;

        if (header)
            h += header->h;

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

    void PropertyFiller::setHeader(std::unique_ptr<SectionHeader> header_)
    {
        header = std::move(header_);
        addAndMakeVisible(header.get());
        resized();
    }

    class EmptyPropertyFiller final : public PropertyFiller
    {
    public:
        void initProperties() override
        {

        }
    };

    std::shared_ptr<PropertyFiller> EMPTY_PROPERTY_FILLER{std::make_shared<EmptyPropertyFiller>()};
}
