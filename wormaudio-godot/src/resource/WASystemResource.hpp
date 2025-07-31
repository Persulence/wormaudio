// Copyright (c)  2025 Thomas Paley-Menzies
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
