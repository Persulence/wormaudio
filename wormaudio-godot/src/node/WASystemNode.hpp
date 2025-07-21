// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <godot_cpp/classes/node.hpp>
#include <resource/SharedResource.hpp>
#include <resource/Project.hpp>
#include <runtime/Runtime.hpp>

#include "../resource/WASystemResource.hpp"

namespace wa
{
    class WAListenerNode;
    class WASoundDef;
}

namespace wa
{
    class WASystemNode : public godot::Node
    {
        GDCLASS(WASystemNode, Node)

    public:
        WASystemNode();
        ~WASystemNode() override;

        [[nodiscard]] godot::Ref<WASystemResource> getSystemResource() const { return systemResource; }
        void setSystemResource(const godot::Ref<WASystemResource> &ref);

        [[nodiscard]] godot::NodePath getListenerPath() const { return listenerPath; }
        void setListenerPath(const godot::NodePath &listenerPath);
        WAListenerNode* getListener();

        void _ready() override;

        resource::Handle<resource::Project> getSystem();

        WASoundDef* getSoundDef(const godot::String &name);

    protected:
        static void _bind_methods();

    private:
        godot::Ref<WASystemResource> systemResource;

        godot::NodePath listenerPath;
        WAListenerNode* listenerCache;

        resource::Handle<resource::Project> system;

        resource::Handle<resource::Project> loadSystem() const;
    };
}
