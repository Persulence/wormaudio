
// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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