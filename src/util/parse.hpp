// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
