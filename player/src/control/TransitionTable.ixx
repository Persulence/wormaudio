module;

#include <memory>
#include <vector>

export module control:TransitionTable;

import :Node;
import :Transition;

namespace sm
{
    struct Entry
    {
        StateInstance node;
        ConditionList transition;
    };

    export class TransitionTable
    {
    private:
        std::vector<Entry> entries;

    public:
        using Ptr = std::shared_ptr<TransitionTable>;

        void insert(Entry&& entry)
        {
            entries.emplace_back(std::move(entry));
        }

        void logicTick(const ParameterLookup& parameters, element::ElementInstanceContext& context)
        {

            // for (auto& [node, transition] : entries)
            // {
            //     if (transition.test(parameters))
            //     {
            //         node.activate(context);
            //     }
            // }
        }
    };
}
