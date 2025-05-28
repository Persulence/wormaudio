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

    void State::insertTransition(const Transition1 &transition)
    {
        transitions.emplace(transition.nextState.lock().get(), transition);
    }

    const std::vector<ElementEntry> & State::elements()
    {
        return elements_;
    }

    const std::unordered_map<State*, Transition1>& State::getTransitions() const
    {
        return transitions;
    }

    const std::string & State::getName()
    {
        return name;
    }
}
