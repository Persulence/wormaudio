// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
