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
}
