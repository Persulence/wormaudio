#include "StateDef.hpp"

#include <memory>
#include <vector>
#include <unordered_map>

#include "juce_core/juce_core.h"

#include "event/ElementHandle.hpp"

#include "state/ConditionList.hpp"

namespace sm
{
    Transition1::Transition1(std::unique_ptr<condition::ConditionList> conditions_, std::weak_ptr<StateDef> nextState_):
        conditions(std::move(conditions_)), nextState(std::move(nextState_))
    {

    }

    StateDef::StateDef()
    // StateDef::StateDef(const std::shared_ptr<automation::AutomationRegistry> &registry)
        // automation(registry)
    {
        // Doesn't work
        // insertTransition(std::make_shared<Transition1>(condition::ConditionList{}, shared_from_this()));
    }

    void StateDef::insertElement(const event::ElementHandle &entry)
    {
        elements.emplace_back(entry);
    }

    void StateDef::removeElement(const resource::Handle<element::Element> &element)
    {
        if (const auto it = std::ranges::find_if(elements, [&element](const auto& e){ return e.ptr == element; }); it != elements.end())
        {
            elements.erase(it);
        }
    }

    void StateDef::insertTransition(const Transition1::Ptr &transition)
    {
        transitionLookup.emplace(transition->nextState.lock().get(), transition);
        transitions.push_back(transition);
    }

    void StateDef::removeTransitionTo(StateDef *other)
    {
        if (const auto it = transitionLookup.find(other); it != transitionLookup.end())
        {
            transitions.erase(std::ranges::remove(transitions, it->second).begin(), transitions.end());
            transitionLookup.erase(it);
        }
    }

    void StateDef::reorderTransition(StateDef *target, int index)
    {
        if (const auto it = transitionLookup.find(target); it != transitionLookup.end())
        {
            auto prevPos = std::ranges::find(transitions, it->second);
            // auto prevIndex = pos - transitions.begin();

            // if (index > prevIndex)
            // {
                // prevIndex += 1;
            // }

            // transitions.insert(transitions.begin() + index, *pos);
            // transitions.erase(transitions.begin() + prevIndex);

            auto pos = transitions.begin();
            std::advance(pos, index);


            transitions.splice(pos, transitions, prevPos);
        }
    }

    void StateDef::setName(const std::string &name_)
    {
        name.setValue(name_);
    }

    bool StateDef::hasSelfTransition()
    {
        return transitionLookup.contains(this);
    }

    const std::vector<event::ElementHandle> & StateDef::getElements()
    {
        return elements;
    }

    const std::unordered_map<StateDef*, Transition1::Ptr>& StateDef::getTransitionLookup() const
    {
        return transitionLookup;
    }

    const std::list<std::shared_ptr<Transition1>>& StateDef::getTransitions() const
    {
        return transitions;
    }

    std::string StateDef::getName() const
    {
        return static_cast<juce::String>(name.getValue()).toStdString();
    }

    std::unique_ptr<StateInstance> createNodeInstance(const std::shared_ptr<StateDef> &node)
    {
        return std::make_unique<StateInstance>(node);
    }
}

