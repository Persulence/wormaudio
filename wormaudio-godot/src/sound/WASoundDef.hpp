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

#include <event/EventDef.hpp>
#include <godot_cpp/classes/ref.hpp>

namespace wa
{
    class WASoundDef : public godot::RefCounted
    {
        GDCLASS(WASoundDef, RefCounted)

    public:
        explicit WASoundDef(std::shared_ptr<event::EventDef> def_);

        resource::Handle<event::EventDef> getBacking() const { return def; }

    protected:
        static void _bind_methods();

    private:
        resource::Handle<event::EventDef> def;

        WASoundDef() = default;

    };
}