// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
JOPT(OptionalString, binding::NEventDef)

%include "util.i"

%include "player.i"
%include "runtime.i"
%include "instance.i"
%include "logger.i"

// --- Binding ---

%ignore "";

EXPOSE(binding)
EXPOSE(binding::sanityCheck)

EXPOSE(binding::NEventDef)
EXPOSE(binding::NEventDef::~NEventDef)
EXPOSE(binding::NEventDef::instantiate)

EXPOSE(binding::NSystem)
EXPOSE(binding::NSystem::~NSystem)
EXPOSE(binding::NSystem::load)
EXPOSE(binding::NSystem::getEventDef)

%javaexception("java.io.IOException") binding::NSystem::load {
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

