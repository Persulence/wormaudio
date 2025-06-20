#pragma once

#include <memory>

#include "event/EventInstance.hpp"

namespace editor
{
    class EditorEventInstance : public event::EventInstance
    {
    public:
        using Ptr = std::shared_ptr<EditorEventInstance>;

        explicit EditorEventInstance(resource::Handle<event::EventDef> parent_);
        void refresh();
    };
}
