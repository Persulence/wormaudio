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
//%include "optional.i"
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

JOPT(OptionalString, std::string)
JOPT(OptionalString, binding::NEventDef)

%define EXPOSE(name)
%rename("%s") name;
%enddef

%ignore "";
//%include "juce_core/system/juce_StandardHeader.h"
//%include "juce_core/system/juce_PlatformDefs.h"
//#include "juce_core/juce_core.h"
%rename("%s") "";

%ignore "";
EXPOSE(binding::NEventDef)
EXPOSE(binding::NEventDef::~NEventDef)

EXPOSE(binding)
EXPOSE(binding::sanityCheck)

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

