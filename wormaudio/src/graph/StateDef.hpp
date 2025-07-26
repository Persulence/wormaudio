// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <memory>
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

        Transition1(std::unique_ptr<condition::ConditionList> conditions_, std::weak_ptr<StateDef> nextState_);

    private:
        FRIEND_CEREAL
        INTERNAL_SERIALIZE
        {
            using namespace cereal;
            ar(
                make_nvp("conditions", conditions),
                make_nvp("nextState", nextState)
                );
        }

        LOAD_AND_CONSTRUCT(Transition1)
        {
            using namespace cereal;

            decltype(conditions) conditions;
            decltype(nextState) nextState;

            ar(
                make_nvp("conditions", conditions),
                make_nvp("nextState", nextState)
                );

            construct(std::move(conditions), nextState);
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

    class StateDef : public resource::SharedResource, public resource::Identifiable, public std::enable_shared_from_this<StateDef>
    {
    public:
        // using Ptr = :Handle<StateDef>;
        using Weak = std::weak_ptr<StateDef>;
        util::Data<std::string> name{"State"};
        Flags flags{NORMAL};

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StateDef)
        StateDef();

        void insertElement(const event::ElementHandle& entry);
        void removeElement(const resource::Handle<element::Element> &element);
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

        void handoff(element::ElementInstanceContext &context, const StateDef *nextState);

    private:
        std::vector<event::ElementHandle> elements;

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
            using namespace cereal;
            make_optional_nvp(ar, "identifiable", base_class<Identifiable>(this));
            ar(
                make_nvp("name", name),
                make_nvp("flags", flags),
                make_nvp("elements", elements),
                make_nvp("transitions", transitions)
                );
        }

        LOAD_AND_CONSTRUCT(StateDef)
        {
            using namespace cereal;

            decltype(name) name;
            decltype(flags) flags;
            decltype(elements) elements;
            decltype(transitions) transitions;

            ar(
                make_nvp("name", name),
                make_nvp("flags", flags),
                make_nvp("elements", elements),
                make_nvp("transitions", transitions)
                );

            construct(elements, transitions);
            construct->name = *name;
            construct->flags = flags;

            ar(make_nvp("identifiable", base_class<Identifiable>(construct.ptr())));
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

        const decltype(instances)& getInstances() const
        {
            return instances;
        }

        void activateAll(element::ElementInstanceContext& context)
        {
            for (auto& entry : parent->getElements())
            {
                // The node instance shares ownership of the element instance with the manager
                auto instance = context.createInstance(*entry);
                instances.emplace_back(instance);
                instance->start();
            }
        }

        void deactivateAll()
        {
            for (const auto& instance : instances)
            {
                instance->stop();
            }

            instances.clear();
        }

        void handoff(element::ElementInstanceContext& context, StateInstance* prevState);

        resource::Handle<StateDef> getParent() const
        {
            return parent;
        }
    };

    std::unique_ptr<StateInstance> createNodeInstance(const std::shared_ptr<StateDef>& node);

    using OnStateChange = signal_event::Callback<resource::Handle<StateDef>>;
}
