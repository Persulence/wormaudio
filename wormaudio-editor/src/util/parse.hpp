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
#include "util/Time.hpp"

namespace ui::parse
{
    template <typename T>
    std::string defaultToString(T t)
    {
        std::ostringstream ss;
        ss << t;
        return ss.str();
    }

    inline player::Seconds parseSeconds(const std::string& str)
    {
        try
        {
            return std::stod(str);
        }
        catch (std::exception&)
        {
            return 0;
        }
    }

    inline player::Beats parseBeats(const std::string& str)
    {
        try
        {
            return std::stod(str);
        }
        catch (std::exception&)
        {
            return 0;
        }
    }

    inline int parseInt(const std::string& str)
    {
        try
        {
            return std::stoi(str);
        }
        catch (std::exception&)
        {
            return 0;
        }
    }

    inline double parseBpm(const std::string& str)
    {
        try
        {
            return std::stod(str);
        }
        catch (std::exception&)
        {
            return 0;
        }
    }

    inline float parseFloat(const std::string& str)
    {
        try
        {
            return std::stof(str);
        }
        catch (std::exception&)
        {
            return 0;
        }
    }
}
