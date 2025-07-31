// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
        conditions(std::move(conditions_)), nextState(std::move(nextState_)) {}

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
        if (const auto it = std::ranges::find_if(elements, [&element](const auto &e) { return e.ptr == element; });
            it != elements.end())
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

    const std::vector<event::ElementHandle> &StateDef::getElements()
    {
        return elements;
    }

    const std::unordered_map<StateDef *, Transition1::Ptr> &StateDef::getTransitionLookup() const
    {
        return transitionLookup;
    }

    const std::list<std::shared_ptr<Transition1> > &StateDef::getTransitions() const
    {
        return transitions;
    }

    std::string StateDef::getName() const
    {
        return static_cast<juce::String>(name.getValue()).toStdString();
    }

    // void StateDef::handoff(element::ElementInstanceContext &context, const StateDef *nextState)
    // {
    //     std::unordered_set<std::shared_ptr<element::Element>> set;
    //     if (nextState)
    //     {
    //         for (auto& element : elements)
    //         {
    //             // if (element->ignoreTransition())
    //             if (true)
    //             {
    //                 if (auto it = std::find(nextState->elements.begin(), nextState->elements.end(), element); it != elements.end())
    //                 {
    //
    //                 }
    //                 else
    //                 {
    //
    //                 }
    //             }
    //         }
    //
    //         std::set_intersection(elements.begin(), elements.end(), nextState->elements.begin(), nextState->elements.end())
    //     }
    // }

    void StateInstance::handoff(element::ElementInstanceContext &context, StateInstance *prevState)
    {
        if (prevState == this)
        {
            for (auto &instance: instances)
            {
                if (instance->getParent()->ignoreStateChange())
                {
                    // Retain play state
                }
                else
                {
                    instance->stop();
                    instance = context.createInstance(*instance->getParent());
                    instance->start();
                }
            }
        }
        else
        {
            std::unordered_set<element::Element *> retained;
            const auto &parentElements = parent->getElements();
            auto &prevInstances = prevState->instances;

            for (auto it = prevInstances.begin(); it != prevInstances.end();)
            {
                // If the previous element ignores state changes and is in the current state, let it continue
                auto &instance = *it;
                auto instanceParent = instance->getParent();
                if (instanceParent->ignoreStateChange())
                {
                    if (auto found = std::ranges::find_if(parentElements, [instanceParent](auto &e)
                    {
                        return e.ptr.get() == instanceParent;
                    }); found != parentElements.end())
                    {
                        // Move the instance here
                        instances.emplace_back(instance);
                        it = prevInstances.erase(it);

                        retained.emplace(instance->getParent());
                    }
                    else
                    {
                        instance->stop();
                        ++it;
                    }
                }
                else
                {
                    instance->stop();
                    ++it;
                }
            }

            prevState->instances.clear();

            for (const auto &element: getParent()->getElements())
            {
                if (!retained.contains(element.ptr.get()))
                {
                    auto i = context.createInstance(*element);
                    instances.emplace_back(i);
                    i->start();
                }
            }
        }
    }

    std::unique_ptr<StateInstance> createNodeInstance(const std::shared_ptr<StateDef> &node)
    {
        return std::make_unique<StateInstance>(node);
    }
}
