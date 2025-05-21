module;

#include <memory>
#include <utility>
#include <vector>

export module Node;

import Element;
import ElementInstance;
import ElementInstanceContext;

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

    // For now only one node type
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
        const std::shared_ptr<Node> parent;
        std::vector<element::ElementInstancePtr> instances;

    public:
        explicit NodeInstance(std::shared_ptr<Node> node):
            parent(std::move(node))
        {

        }

        void activate(element::ElementInstanceContext& context)
        {
            for (auto& entry : parent->elements())
            {
                // The node instance shares ownership of the element instance with the manager
                auto instance = context.createInstance(*entry.value);
                instances.emplace_back(instance);
                instance->start();
            }
        }

        void deactivate(element::ElementInstanceContext& context)
        {
            for (const auto& instance : instances)
            {
                instance->stop();
            }

            instances.clear();
        }
    };

    export std::unique_ptr<NodeInstance> createNodeInstance(const std::shared_ptr<Node>& node)
    {
        return std::make_unique<NodeInstance>(node);
    }
}