module;

#include <memory>
#include <vector>
#include <unordered_map>
#include "../event/ElementHandle.hpp"

module sm;

import element;

namespace sm
{
    StateDef::StateDef()
    // StateDef::StateDef(const std::shared_ptr<automation::AutomationRegistry> &registry)
        // automation(registry)
    {

    }

    void StateDef::insertElement(const event::ElementHandle &entry)
    {
        elements_.emplace_back(entry);
    }

    void StateDef::removeElement(const event::ElementHandle &element)
    {
        if (const auto it = std::ranges::find_if(elements_, [&element](const auto& e){ return e.ptr == element.ptr; }); it != elements_.end())
        {
            elements_.erase(it);
        }
    }

    void StateDef::insertTransition(const Transition1::Ptr &transition)
    {
        transitions.emplace(transition->nextState.lock().get(), transition);
    }

    void StateDef::removeTransitionTo(StateDef *other)
    {
        if (const auto it = transitions.find(other); it != transitions.end())
        {
            transitions.erase(it);
        }
    }

    void StateDef::setName(const std::string &name_)
    {
        name = name_;
    }

    const std::vector<event::ElementHandle> & StateDef::elements()
    {
        return elements_;
    }

    const std::unordered_map<StateDef*, Transition1::Ptr>& StateDef::getTransitions() const
    {
        return transitions;
    }

    std::string StateDef::getName()
    {
        return name;
    }
}
