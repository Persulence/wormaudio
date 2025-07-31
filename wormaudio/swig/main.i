// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

%module(directors="1") WormAudioInternal

%{
#include "juce_core/juce_core.h"

#include "bindings.h"

#include "event/EventDef.hpp"
#include "resource/SharedResource.hpp"
%}

%include <std_shared_ptr.i>
%include <std_string.i>
%include <std_shared_ptr.i>
%include "java/nullable_java.i"

// Nullable typemaps
JOPT(OptionalString, std::string)
JOPT(OptionalString, binding::WASoundDef)

%include "util.i"

%include "player.i"
%include "runtime.i"
%include "instance.i"
%include "logger.i"

// --- Binding ---

%ignore "";

EXPOSE(binding)
EXPOSE(binding::sanityCheck)

EXPOSE(binding::WASoundDef)
EXPOSE(binding::WASoundDef::~WASoundDef)
EXPOSE(binding::WASoundDef::instantiate)

EXPOSE(binding::WASystem)
EXPOSE(binding::WASystem::~WASystem)
EXPOSE(binding::WASystem::load)
EXPOSE(binding::WASystem::getEventDef)

%javaexception("java.io.IOException") binding::WASystem::load {
    try
    {
        $action
    }
    catch (std::exception& e)
    {
        jclass clazz = jenv->FindClass("java/io/IOException");
        jenv->ThrowNew(clazz, e.what());
        return $null;
    }
}

%include "bindings.h"

%rename("%s") "";

//%include "util/serialization_util.hpp"
//%include "resource/SharedResource.hpp"
//%include "event/EventDef.hpp"

