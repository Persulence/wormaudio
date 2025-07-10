#pragma once

#include <iostream>
#include <filesystem>

#include "juce_core/juce_core.h"

#include "event/EventDef.hpp"
#include "resource/Project.hpp"
#include "event/EventInstance.hpp"
#include "resource/SharedResource.hpp"


// SWIG preprocessor doesn't recurse into all included files, and JUCE uses a lot of macros
#define NS_LEAK_DETECTOR(OwnerClass) \
    friend class juce::LeakedObjectDetector<OwnerClass>; \
    static const char* getLeakedObjectClassName() noexcept { return #OwnerClass; } \
    juce::LeakedObjectDetector<OwnerClass> leakDetector;

// A base that provides leak detection so that we can hopefully detect java silliness.
class WrapperBase
{
private:
    NS_LEAK_DETECTOR(WrapperBase)
};

inline void ooere()
{
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

// class NoClass
// {
// public:
//     NoClass() = default;
//     void thing()
//     {
//         std::cout << "NoClass: thing!" << "\n";
//     }
//     ~NoClass() = default;
// };

// inline void freeFunction(NoClass& nc)
// {
//     nc.thing();
// }


// class NEventDef;

// class NSoundInstance
// {
//     std::shared_ptr<event::EventInstance> instance;
//     const NEventDef *parent;
//
// public:
//     explicit NSoundInstance(const NEventDef* parent);
//
//     ~NSoundInstance()
//     {
//         std::cout << "NSoundInstance destroyed" << this << "\n";
//         instance->setPosition({0, 0, 0});
//         instance = nullptr;
//     }
// };

class NSystem;

class NEventDef : WrapperBase
{
public:
    // NSoundInstance instantiate() const;

private:
    friend class NSoundInstance;
    friend class NSystem;

    resource::Handle<event::EventDef> eventDef;

    explicit NEventDef(resource::Handle<event::EventDef> eventDef_): eventDef(std::move(eventDef_))
    {
    }
};


class NSystem : WrapperBase
{
public:
    static NSystem load(const std::string& path)
    {
        resource::Handle<resource::Project> project = resource::make<resource::Project>(std::make_unique<asset::AssetManager>(false));

        return NSystem{project};
    }

    // std::optional<NEventDef> getEventDef(const std::string& name) const
    std::optional<std::string> getEventDef(const std::string& name) const
    {
        if (const auto ret = project->getEvent(name))
        {
            return "oooer";
            // return NEventDef{*ret};
        }

        return {};
    }

private:
    resource::Handle<resource::Project> project;

    explicit NSystem(decltype(project) project_): project(std::move(project_))
    {

    }
};

// inline NSoundInstance::NSoundInstance(const NEventDef *parent):
//     parent(parent)
// {
//     std::cout << "NSoundInstance created\n";
//     instance = parent->eventDef->instantiate();
// }
//
// inline NSoundInstance NEventDef::instantiate() const
// {
//     return NSoundInstance{this};
// }