module;

#include <memory>
#include <vector>

export module control;

import Node;
import ParameterLookup;
export import :Transition;

namespace sm
{
    struct Entry
    {
        std::shared_ptr<NodeInstance> node;
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
            for (auto& [node, transition] : entries)
            {
                if (transition.test(parameters))
                {
                    // node.ac
                }
            }
        }
    };
}

