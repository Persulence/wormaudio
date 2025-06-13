module;

#include <unordered_map>
#include <memory>
#include <utility>
#include <vector>

#include <juce_core/juce_core.h>

#include "../event/ElementHandle.hpp"

export module sm:Node;

import element;
import ElementInstance;

import :Transition;

namespace sm
{
    export class StateDef;

    export class Transition1
    {
    public:
        using Ptr = std::shared_ptr<Transition1>;

        condition::ConditionList conditions;
        std::weak_ptr<StateDef> nextState;

        Transition1(condition::ConditionList conditions_, std::weak_ptr<StateDef> nextState_):
            conditions(std::move(conditions_)), nextState(std::move(nextState_))
        { }
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
    export class StateDef : public std::enable_shared_from_this<StateDef>
    {
    public:
        using Ptr = std::shared_ptr<StateDef>;
        using Weak = std::weak_ptr<StateDef>;
        std::string name{"State"};
        Flags flags{NORMAL};

    private:
        std::vector<event::ElementHandle> elements_;
        // std::shared_ptr<automation::AutomationRegistry> automation;

        // Using raw pointers as keys as they are non-owning and won't block disposal of cyclic graphs.
        // std::weak_ptr doesn't work as a key
        // Just need to find a way to indicate that keys shouldn't be dereferenced.
        std::unordered_map<StateDef*, std::shared_ptr<Transition1>> transitions;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StateDef)

    public:
        // StateDef(const std::shared_ptr<automation::AutomationRegistry> &registry);
        StateDef();

        void insertElement(const event::ElementHandle& entry);
        void removeElement(const event::ElementHandle& element);
        void insertTransition(const Transition1::Ptr& transition);
        void removeTransitionTo(StateDef* other);
        void setName(const std::string &name_);

        const std::vector<event::ElementHandle>& elements();
        const std::unordered_map<StateDef*, Transition1::Ptr>& getTransitions() const;

        std::string getName();
    };

    export class StateInstance
    {
        std::shared_ptr<StateDef> parent;
        std::vector<element::ElementInstancePtr> instances;

    public:
        // JUCE_DECLARE_NON_COPYABLE(NodeInstance)
        StateInstance(StateInstance&&) = default;
        StateInstance& operator=(StateInstance&&) = default;

        explicit StateInstance(StateDef::Ptr parent_):
            parent(std::move(parent_))
        {

        }

        [[nodiscard]] Flags getFlags() const
        {
            return parent->flags;
        }

        [[nodiscard]] std::string getName() const
        {
            return parent->name;
        }

        void activate(element::ElementInstanceContext& context)
        {
            for (auto& entry : parent->elements())
            {
                // The node instance shares ownership of the element instance with the manager
                auto instance = context.createInstance(*entry);
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

    export std::unique_ptr<StateInstance> createNodeInstance(const std::shared_ptr<StateDef>& node)
    {
        return std::make_unique<StateInstance>(node);
    }
}