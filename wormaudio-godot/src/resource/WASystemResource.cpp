
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

#include "WASystemResource.hpp"

namespace wa
{
    void WASystemResource::_bind_methods()
    {
        using namespace godot;
        ClassDB::bind_method(D_METHOD("get_system_path"), &WASystemResource::getFilePath);
        ClassDB::bind_method(D_METHOD("set_system_path", "p_path"), &WASystemResource::setFilePath);

        ADD_PROPERTY(PropertyInfo(Variant::STRING, "path", PROPERTY_HINT_FILE, "*.proj,*.waproj"), "set_system_path", "get_system_path");
    }
}