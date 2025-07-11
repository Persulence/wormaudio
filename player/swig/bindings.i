%module NEEPSound

// Add necessary symbols to generated header
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

%pragma(java) jniclasscode=%{
  static {
    try {
        System.loadLibrary("neepsound-java");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library failed to load. \n" + e);
      System.exit(1);
    }
  }
%}

// Nullable typemaps
JOPT(OptionalString, std::string)
JOPT(OptionalString, binding::NEventDef)

%include "util.i"

%include "runtime.i"

%shared_ptr(event::EventInstance)

%ignore "";
EXPOSE(event)
EXPOSE(event::EventInstance)
EXPOSE(event::~EventInstance)
EXPOSE(event::EventInstance::stop)

%include "event/EventInstance.hpp"
%rename("%s") "";

%include "runtime.i"

// --- Binding ---

%ignore "";

EXPOSE(binding)
EXPOSE(binding::sanityCheck)

EXPOSE(binding::NEventDef)
EXPOSE(binding::NEventDef::~NEventDef)
EXPOSE(binding::NEventDef::instantiate)

EXPOSE(binding::NEventInstance)
EXPOSE(binding::NEventInstance::~NEventInstance)

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

