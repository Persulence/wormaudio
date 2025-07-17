// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <iostream>
#include <filesystem>

#include "juce_core/juce_core.h"

#include "event/EventDef.hpp"
#include "resource/Project.hpp"
// #include "event/EventInstance.hpp"
#include "Nullable.hpp"
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

namespace binding
{
    void sanityCheck();
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



namespace binding
{
    class NSystem;
    class NEventDef;

    // class NEventInstance : WrapperBase
    // {
    //     std::shared_ptr<event::EventInstance> instance;
    //
    // public:
    //     explicit NEventInstance(std::shared_ptr<event::EventInstance> instance_): instance(std::move(instance_)) {};
    //
    //     ~NEventInstance()
    //     {
    //     }
    // };

    class NEventDef : WrapperBase
    {
    private:
        friend class NEventInstance;
        friend class NSystem;
        friend class NRuntime;

        resource::Handle<event::EventDef> eventDef;

        explicit NEventDef(resource::Handle<event::EventDef> eventDef_): eventDef(std::move(eventDef_))
        {
        }
    };

    class NSystem : WrapperBase
    {
    public:
        static NSystem load(const std::string& path);

        [[nodiscard]] binding::Nullable<NEventDef> getEventDef(const std::string& name) const
        {
            if (const auto ret = project->getEvent(name))
            {
                return NEventDef{*ret};
            }

            return {};
        }

    private:
        resource::Handle<resource::Project> project;

        explicit NSystem(decltype(project) project_): project(std::move(project_))
        {

        }
    };
}

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