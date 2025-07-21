// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <godot_cpp/classes/resource.hpp>

namespace wa
{
    class WASystemResource : public godot::Resource
    {
        GDCLASS(WASystemResource, Resource)

    public:
        static void _bind_methods();

        [[nodiscard]] godot::String getFilePath() const { return systemPath; }
        void setFilePath(const godot::String &filePath) { this->systemPath = filePath; }

    private:
        godot::String systemPath;
    };
} // wa
