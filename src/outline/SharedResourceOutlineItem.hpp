#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "juce_opengl/juce_opengl.h"
#include "resource/SharedResource.hpp"

namespace ui
{
    template <class T>
    class SharedResourceItem : public juce::TreeViewItem
    {
    public:
        explicit SharedResourceItem(const resource::Handle<T> &resource):
            resource(resource)
        {

        }

        void itemOpennessChanged(bool isNowOpen) override
        {
            refresh(true);
        }

        void refresh(bool clear = true)
        {
            if (getOpenness() == Openness::opennessOpen)
            {
                if (clear)
                    clearSubItems();

                for (auto child : resource->getChildResources())
                {
                    auto result = OutlineTypeRegistry::getInstance().get(child);
                    addSubItem(result.release());
                }
            }
            else
            {
                clearSubItems();
            }
        }

        bool mightContainSubItems() override
        {
            return true;
        }

        std::unique_ptr<juce::Component> createItemComponent() override
        {
            return std::make_unique<OutlineItemComponent>("icon/file.png", false);
        }

        resource::Handle<T> resource;
    };
}
