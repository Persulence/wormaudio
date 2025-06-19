module;

#include <memory>
#include <vector>
#include <unordered_map>

#include "juce_core/juce_core.h"

#include "event/ElementHandle.hpp"

module sm;

namespace sm
{
    StateDef::StateDef()
    // StateDef::StateDef(const std::shared_ptr<automation::AutomationRegistry> &registry)
        // automation(registry)
    {
        // Doesn't work
        // insertTransition(std::make_shared<Transition1>(condition::ConditionList{}, shared_from_this()));
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
        name.setValue(juce::String{name_});
    }

    bool StateDef::hasSelfTransition()
    {
        return transitions.contains(this);
    }

    const std::vector<event::ElementHandle> & StateDef::elements()
    {
        return elements_;
    }

    const std::unordered_map<StateDef*, Transition1::Ptr>& StateDef::getTransitions() const
    {
        return transitions;
    }

    std::string StateDef::getName() const
    {
        return static_cast<juce::String>(name.getValue()).toStdString();
    }
}
