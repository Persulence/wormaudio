#pragma once

#include <iostream>

// #include "resource/Project.hpp"
#include "event/EventDef.hpp"
#include "resource/SharedResource.hpp"
// #include "java/java_alloc.hpp"

inline void ooere()
{
    // resource::Handle<resource::Project> i = resource::make<resource::Project>();
    std::cout << "ooer\n";
}

class SoundThing
{
public:
    int field;

    void memberFunction() const
    {
        std::cout << "field: " << field << "\n";
    }
};

class NEventDef;

class NSoundInstance
{
    std::shared_ptr<event::EventInstance> instance;
    const NEventDef *parent;

public:
    explicit NSoundInstance(const NEventDef* parent);

    ~NSoundInstance()
    {
        std::cout << "NSoundInstance destroyed\n";
    }
};

class NEventDef
{
    resource::Handle<event::EventDef> eventDef;

public:
    NEventDef(): eventDef(event::EventDef::create())
    {
        std::cout << "NEventDef created\n";
    }

    NSoundInstance instantiate() const;

    friend class NSoundInstance;

    ~NEventDef()
    {
        std::cout << "NEventDef destroyed\n";
    }
};

inline NSoundInstance::NSoundInstance(const NEventDef *parent):
    parent(parent)
{
    std::cout << "NSoundInstance created\n";
    instance = parent->eventDef->instantiate();
}

inline NSoundInstance NEventDef::instantiate() const
{
    return NSoundInstance{this};
}