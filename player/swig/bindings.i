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



%define EXPOSE(name)
%rename("%s") name;
%enddef

%ignore "";
//%include "juce_core/system/juce_StandardHeader.h"
//%include "juce_core/system/juce_PlatformDefs.h"
//#include "juce_core/juce_core.h"
%rename("%s") "";

%ignore "";
%rename("%s") NEventDef;
%rename("%s") NEventDef::~NEventDef;

EXPOSE(NSystem)
EXPOSE(NSystem::~NSystem)
EXPOSE(NSystem::getEventDef)

%include "bindings.h"

%rename("%s") "";

//%include "util/serialization_util.hpp"
//%include "resource/SharedResource.hpp"
//%include "event/EventDef.hpp"

