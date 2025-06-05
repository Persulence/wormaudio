#pragma once

#include <memory>

import event;

namespace editor
{
    class EditorEventInstance : public event::EventInstance
    {
    public:
        using Ptr = std::shared_ptr<EditorEventInstance>;

        EditorEventInstance(event::Event::Ptr parent_);
        void refresh();
    };
}
