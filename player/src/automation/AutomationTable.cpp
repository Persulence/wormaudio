#include "AutomationTable.hpp"

namespace automation
{
    void AutomationTable::setup(const AutomationLink& link)
    {
        links.push_back(link);
    }
}
