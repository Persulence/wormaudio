module;

#include <memory>
#include <vector>
#include <unordered_map>

module control;

import element;

namespace sm
{
    void State::insertElement(const std::shared_ptr<element::Element> &entry)
    {
        elements_.emplace_back(entry);
    }

    void State::insertTransition(const Transition1::Ptr &transition)
    {
        transitions.emplace(transition->nextState.lock().get(), transition);
    }

    void State::removeTransitionTo(State *other)
    {
        if (const auto it = transitions.find(other); it != transitions.end())
        {
            transitions.erase(it);
        }
    }

    void State::setName(const std::string &name_)
    {
        name = name_;
    }

    const std::vector<ElementEntry> & State::elements()
    {
        return elements_;
    }

    const std::unordered_map<State*, Transition1::Ptr>& State::getTransitions() const
    {
        return transitions;
    }

    std::string State::getName()
    {
        return name;
    }
}
