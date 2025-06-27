#include "ElementInspectorFiller.hpp"

#include "panel/MyPropertyPanel.hpp"
#include "resource/ChoiceElement.hpp"
#include "resource/ClipElement.hpp"

namespace ui
{
    using namespace element;

    namespace element_property_filler
    {
        class ClipImpl : public PropertyFiller
        {
            ClipElement& element;

        public:
            explicit ClipImpl(ClipElement &element) :
                element(element)
            {
                setHeader(std::make_unique<SectionHeader>("Clip Element"));
            }

            void initProperties() override
            {
                add(std::make_shared<BoolDataPropertyWidget>("Loop", element.loop));
            }
        };

        class ChoiceImpl : public PropertyFiller
        {
            ChoiceElement& element;

        public:
            explicit ChoiceImpl(ChoiceElement &element) :
                element(element)
            {
                setHeader(std::make_unique<SectionHeader>("Choice Element"));
            }

            void initProperties() override
            {
                add(std::make_shared<BoolDataPropertyWidget>("Loop", element.loop));
            }
        };
    }

    ElementInspectorFiller::ElementInspectorFiller(event::ElementHandle handle_):
        handle(std::move(handle_))
    {
        ElementInspectorFiller::initProperties();
    }

    void ElementInspectorFiller::initProperties()
    {
        // Urgh
        if (typeid(*handle.ptr) == typeid(ClipElement))
        {
            add(std::make_shared<element_property_filler::ClipImpl>(dynamic_cast<ClipElement&>(*handle.ptr)));
        }
        else if (typeid(*handle.ptr) == typeid(ChoiceElement))
        {
            add(std::make_shared<element_property_filler::ChoiceImpl>(dynamic_cast<ChoiceElement&>(*handle.ptr)));
        }
    }
}
