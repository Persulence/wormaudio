module;

#include <memory>
#include <vector>

export module control;

import Node;
import ParameterLookup;
export import :Transition;

struct Entry
{
// public:
    std::shared_ptr<Node> node;
    Transition transition;
};

export class TransitionTable
{
private:
    std::vector<Entry> entries;

public:
    void insert(Entry&& entry)
    {
        entries.push_back(std::move(entry));
    }

    void logicTick(const ParameterLookup& parameters)
    {
        for (auto& entry : entries)
        {
            bool result = entry.transition.test(parameters);
            if (result)
            {
                entry.node->activate();
            }
        }
    }
};
