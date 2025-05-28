module;

#include <unordered_map>
#include <memory>
#include <utility>
#include <vector>

#include <juce_core/juce_core.h>

export module control:Node;

import element;
import ElementInstance;

import :Transition;

namespace sm
{
    export class State;

    export struct Transition1
    {
        Transition1(ConditionList conditions_, std::weak_ptr<State> nextState_):
            conditions(std::move(conditions_)), nextState(std::move(nextState_))
        { }

        ConditionList conditions;
        std::weak_ptr<State> nextState;
    };

    export struct ElementEntry
    {
        std::shared_ptr<element::Element> value;

        const element::Element* operator->() const
        {
            return value.get();
        }
    };

    // For now only one state type
    export class State
    {
    public:
        using Ptr = std::shared_ptr<State>;
        using Weak = std::weak_ptr<State>;
        std::string name{"State"};

    private:
        std::vector<ElementEntry> elements_;

        // Using raw pointers as keys as they are non-owning and won't block disposal of cyclic graphs.
        // std::weak_ptr doesn't work as a key
        // Just need to find a way to indicate that keys shouldn't be dereferenced.
        std::unordered_map<State*, Transition1> transitions;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(State)

    public:
        State() = default;

        void insertElement(const std::shared_ptr<element::Element>& entry);
        void insertTransition(const Transition1& transition);
        void removeTransitionTo(State* other);

        const std::vector<ElementEntry>& elements();
        const std::unordered_map<State*, Transition1>& getTransitions() const;

        const std::string& getName();
    };

    export class StateInstance
    {
        std::shared_ptr<State> parent;
        std::vector<element::ElementInstancePtr> instances;

    public:
        // JUCE_DECLARE_NON_COPYABLE(NodeInstance)
        StateInstance(StateInstance&&) = default;
        StateInstance& operator=(StateInstance&&) = default;

        explicit StateInstance(State::Ptr parent_):
            parent(std::move(parent_))
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

        void deactivate()
        {
            for (const auto& instance : instances)
            {
                instance->stop();
            }

            instances.clear();
        }
    };

    export std::unique_ptr<StateInstance> createNodeInstance(const std::shared_ptr<State>& node)
    {
        return std::make_unique<StateInstance>(node);
    }
}