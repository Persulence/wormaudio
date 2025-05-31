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

    export class Transition1
    {
    public:
        using Ptr = std::shared_ptr<Transition1>;

        condition::ConditionList conditions;
        std::weak_ptr<State> nextState;

        Transition1(condition::ConditionList conditions_, std::weak_ptr<State> nextState_):
            conditions(std::move(conditions_)), nextState(std::move(nextState_))
        { }
    };

    export struct ElementEntry
    {
        std::shared_ptr<element::Element> value;

        const element::Element* operator->() const
        {
            return value.get();
        }
    };

    export enum StateType
    {
        START,
        NORMAL,
        END
    };

    export struct Flags
    {
        StateType type;
    };

    // For now only one state type
    export class State
    {
    public:
        using Ptr = std::shared_ptr<State>;
        using Weak = std::weak_ptr<State>;
        std::string name{"State"};
        Flags flags{NORMAL};

    private:
        std::vector<ElementEntry> elements_;

        // Using raw pointers as keys as they are non-owning and won't block disposal of cyclic graphs.
        // std::weak_ptr doesn't work as a key
        // Just need to find a way to indicate that keys shouldn't be dereferenced.
        std::unordered_map<State*, std::shared_ptr<Transition1>> transitions;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(State)

    public:
        State() = default;

        void insertElement(const std::shared_ptr<element::Element>& entry);
        void insertTransition(const Transition1::Ptr& transition);
        void removeTransitionTo(State* other);
        void setName(const std::string &name_);

        const std::vector<ElementEntry>& elements();
        const std::unordered_map<State*, Transition1::Ptr>& getTransitions() const;

        std::string getName();
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

        Flags getFlags()
        {
            return parent->flags;
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