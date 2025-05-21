module;

#include <memory>
#include <utility>
#include <vector>

export module Node;

import Element;
import ElementInstance;

namespace sm
{
    export struct ElementEntry
    {
        std::shared_ptr<element::Element> value;

        const element::Element* operator->() const
        {
            return value.get();
        }
    };

    // For now only one node subtype
    export class Node
    {
        std::vector<ElementEntry> elements_;
    public:
        void insertElement(const std::shared_ptr<element::Element>& entry)
        {
            elements_.emplace_back(entry);
        }

        const std::vector<ElementEntry>& elements()
        {
            return elements_;
        }
    };

    export class NodeInstance
    {
        std::shared_ptr<Node> parent;
        std::vector<std::shared_ptr<element::ElementInstance>> instances;

    public:
        explicit NodeInstance(std::shared_ptr<Node> node):
            parent(std::move(node))
        {

        }

        void activate()
        {
            for (auto& entry : parent->elements())
            {
                // Fine for oneshots
                auto& ret = instances.emplace_back(entry->createInstance());
                ret->activate();
            }
        }
    };

    export std::unique_ptr<NodeInstance> createNodeInstance(const std::shared_ptr<Node>& node)
    {
        return std::make_unique<NodeInstance>(node);
    }
}