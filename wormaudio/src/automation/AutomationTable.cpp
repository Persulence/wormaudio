// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "AutomationTable.hpp"

namespace automation
{
    void AutomationTable::setup(const AutomationLink& link)
    {
        links.push_back(link);
    }
}
