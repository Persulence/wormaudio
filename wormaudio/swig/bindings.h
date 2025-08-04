// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
public:
    virtual ~WrapperBase() = default;

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

namespace binding
{
    class WASystem;
    class WASoundDef;

    class WASoundDef : WrapperBase
    {
    private:
        friend class NEventInstance;
        friend class WASystem;
        friend class WARuntime;

        resource::Handle<event::EventDef> eventDef;

        explicit WASoundDef(resource::Handle<event::EventDef> eventDef_): eventDef(std::move(eventDef_))
        {
        }
    };

    class WASystem : WrapperBase
    {
    public:
        static WASystem load(const std::string& path);

        [[nodiscard]] binding::Nullable<WASoundDef> getEventDef(const std::string& name) const
        {
            if (const auto ret = project->getEvent(name))
            {
                return WASoundDef{*ret};
            }

            return {};
        }

    private:
        resource::Handle<resource::Project> project;

        explicit WASystem(decltype(project) project_): project(std::move(project_))
        {

        }
    };
}