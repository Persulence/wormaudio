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

        resource::Handle<T> resource;
    };
}
