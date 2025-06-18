#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
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
            if (isNowOpen)
            {
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

        resource::Handle<T> resource;
    };
}
