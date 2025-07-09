#pragma once

#include <iostream>

// #include "resource/Project.hpp"
#include "event/EventDef.hpp"
#include "resource/SharedResource.hpp"
#include "java/java_alloc.hpp"

inline void ooere()
{
    // resource::Handle<resource::Project> i = resource::make<resource::Project>();
    std::cout << "ooer\n";
}

class NEventDef;

class NSoundInstance
{
    std::shared_ptr<event::EventInstance> instance;
    const NEventDef *parent;

public:
    explicit NSoundInstance(const NEventDef* parent);
};

class NEventDef
{
    resource::Handle<event::EventDef> eventDef;

public:
    NSoundInstance* instantiate() const;

    friend class NSoundInstance;
};

inline NSoundInstance::NSoundInstance(const NEventDef *parent):
    parent(parent)
{
    instance = parent->eventDef->instantiate();
}

inline NSoundInstance * NEventDef::instantiate() const
{
    return new NSoundInstance{this};
}