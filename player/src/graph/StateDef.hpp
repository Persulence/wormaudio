#pragma once

#include <unordered_map>
#include <memory>
#include <ranges>
#include <utility>
#include <vector>

#include "cereal/types/list.hpp"

#include "juce_core/juce_core.h"

#include "util/Data.hpp"

#include "event/ElementHandle.hpp"
#include "resource/ElementInstance.hpp"
#include "resource/ElementInstanceContext.hpp"
#include "resource/SharedResource.hpp"
#include "signal/Signal.hpp"

#include "state/ConditionList.hpp"

namespace sm
{
    class StateDef;

    class Transition1 : public resource::SharedResource
    {
    public:
        using Ptr = std::shared_ptr<Transition1>;

        std::unique_ptr<condition::ConditionList> conditions;
        std::weak_ptr<StateDef> nextState;

        Transition1(const condition::ConditionList& conditions_, std::weak_ptr<StateDef> nextState_);

    private:
        FRIEND_CEREAL
        INTERNAL_SERIALIZE
        {
            ar(
                cereal::make_nvp("conditions", conditions),
                cereal::make_nvp("nextState", nextState)
                );
        }

        LOAD_AND_CONSTRUCT(Transition1)
        {
            decltype(conditions) conditions;
            decltype(nextState) nextState;

            ar(
                cereal::make_nvp("conditions", conditions),
                cereal::make_nvp("nextState", nextState)
                );

            construct(*conditions, nextState);
        }
    };

    enum StateType
    {
        START,
        NORMAL,
        END
    };

    struct Flags
    {
        StateType type;

        INTERNAL_SERIALIZE
        {
            ar(CEREAL_NVP(type));
        }
    };

    // For now only one state type

    class StateDef : public resource::SharedResource, public std::enable_shared_from_this<StateDef>
    {
    public:
        // using Ptr = :Handle<StateDef>;
        using Weak = std::weak_ptr<StateDef>;
        util::Data<std::string> name{"State"};
        Flags flags{NORMAL};

    public:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StateDef)
        // StateDef(const std::shared_ptr<automation::AutomationRegistry> &registry);
        StateDef();

        void insertElement(const event::ElementHandle& entry);
        void removeElement(const event::ElementHandle& element);
        void insertTransition(const Transition1::Ptr& transition);
        void removeTransitionTo(StateDef* other);
        void reorderTransition(StateDef* target, int index);
        void setName(const std::string &name_);

        bool hasSelfTransition();
        const std::vector<event::ElementHandle>& getElements();
        const std::unordered_map<StateDef*, Transition1::Ptr>& getTransitionLookup() const;
        const std::list<std::shared_ptr<Transition1>>& getTransitions() const;

        std::string getName() const;

        std::vector<resource::ResourceHandle> getChildResources() override
        {
            // auto values = transitions | std::views::values;
            return std::vector<resource::ResourceHandle>{transitions.begin(), transitions.end()};
        }

    private:
        std::vector<event::ElementHandle> elements;
        // std::shared_ptr<automation::AutomationRegistry> automation;

        std::list<std::shared_ptr<Transition1>> transitions;
        // Using raw pointers as keys as they are non-owning and won't block disposal of cyclic graphs.
        // std::weak_ptr doesn't work as a key
        // Just need to find a way to indicate that keys shouldn't be dereferenced.
        std::unordered_map<StateDef*, std::shared_ptr<Transition1>> transitionLookup;

        // OOHH MYY GODDD
        StateDef(const decltype(elements)& elements_, const decltype(transitions)& transitions_):
            elements(elements_),
            transitions(transitions_)
        {
            for (auto& transition : transitions)
            {
                if (auto shared = transition->nextState.lock())
                {
                    transitionLookup[shared.get()] = transition;
                }
            }
        }

        FRIEND_CEREAL

        INTERNAL_SERIALIZE
        {
            ar(
                cereal::make_nvp("name", name),
                cereal::make_nvp("flags", flags),
                cereal::make_nvp("elements", elements),
                cereal::make_nvp("transitions", transitions)
                );
        }

        LOAD_AND_CONSTRUCT(StateDef)
        {
            decltype(name) name;
            decltype(flags) flags;
            decltype(elements) elements;
            decltype(transitions) transitions;

            ar(
                cereal::make_nvp("name", name),
                cereal::make_nvp("flags", flags),
                cereal::make_nvp("elements", elements),
                cereal::make_nvp("transitions", transitions)
                );

            construct(elements, transitions);
            construct->name = *name;
            construct->flags = flags;
        }
    };

    class StateInstance
    {
        std::shared_ptr<StateDef> parent;
        std::vector<element::ElementInstancePtr> instances;

    public:
        // JUCE_DECLARE_NON_COPYABLE(NodeInstance)
        StateInstance(StateInstance&&) = default;
        StateInstance& operator=(StateInstance&&) = default;

        explicit StateInstance(resource::Handle<StateDef> parent_):
            parent(std::move(parent_))
        {

        }

        [[nodiscard]] Flags getFlags() const
        {
            return parent->flags;
        }

        [[nodiscard]] std::string getName() const
        {
            return parent->getName();
        }

        void activate(element::ElementInstanceContext& context)
        {
            for (auto& entry : parent->getElements())
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

        resource::Handle<StateDef> getParent() const
        {
            return parent;
        }
    };

    std::unique_ptr<StateInstance> createNodeInstance(const std::shared_ptr<StateDef>& node);

    using OnStateChange = signal_event::Callback<resource::Handle<StateDef>>;
}
